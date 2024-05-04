async function renderPdfDoc(Data, scale, highlight = null) {
    // atob() is used to convert base64 encoded PDF to binary-like data.
    // (See also https://developer.mozilla.org/en-US/docs/Web/API/WindowBase64/
    // Base64_encoding_and_decoding.)
    var pdfData = atob(Data);

    // Loaded via <script> tag, create shortcut to access PDF.js exports.
    var { pdfjsLib, pdfAnnotate } = globalThis;

    // The workerSrc property shall be specified.
    pdfjsLib.GlobalWorkerOptions.workerSrc = 'lib/pdfjs/build/pdf.worker.mjs';

    var pdfDoc = null,
        pagesDiv = document.getElementById('pagesDiv'),
        txtDiv = document.getElementById('txtDiv'),
        root = document.querySelector(':root');

    txtDiv.hidden = true;
    pagesDiv.hidden = false;

    root.style.setProperty('--page-margin', '0 0');
    root.style.setProperty('--page-border', '0');

    // set scale factor
    pagesDiv.style.setProperty('--scale-factor', scale);

    async function renderPage(num) {
        // await for page
        var page = await pdfDoc.getPage(num);

        function createPageDiv(pageNum) {
            var canvas, textLayer, annotationLayer;
            // find old page or make a new one
            var pageDiv = document.querySelector(`.page[pageNum='${pageNum}']`);
            if (!pageDiv) {
                pageDiv = document.createElement('div');
                pageDiv.setAttribute("pageNum", pageNum);
                pageDiv.classList.add('page');
                pagesDiv.appendChild(pageDiv);

                // add canvas for the pdf rendering
                canvas = document.createElement('canvas');
                canvas.id = `pdfCanvas${pageNum}`;
                pageDiv.appendChild(canvas);

                // add div for the text selection layer
                textLayer = document.createElement('div');
                textLayer.id = `textLayer${pageNum}`;
                textLayer.classList.add('textLayer');
                pageDiv.appendChild(textLayer);

                // add div for the annotation layer
                annotationLayer = document.createElement('div');
                annotationLayer.id = `annotationLayer${pageNum}`;
                annotationLayer.classList.add('annotationLayer');
                pageDiv.appendChild(annotationLayer);
            }
            else {
                canvas = pageDiv.childNodes.item(`pdfCanvas${pageNum}`);
                textLayer = pageDiv.childNodes.item(`textLayer${pageNum}`);
                annotationLayer = pageDiv.childNodes.item(`annotationLayer${pageNum}`);
            }
            return { pageDiv: pageDiv, canvas: canvas, textLayer: textLayer, annotationLayer: annotationLayer };
        }
        var { pageDiv, canvas, textLayer, annotationLayer } = createPageDiv(num);

        var viewport = page.getViewport({ scale: scale });

        // set canvas size to that of the viewport
        canvas.height = viewport.height;
        canvas.width = viewport.width;

        pageDiv.style.width = canvas.width + 'px';
        pageDiv.style.height = canvas.height + 'px';

        // set size of pdfViewer to first page dimensions, and render other pages
        if (num == 1) {
            pagesDiv.style.width = canvas.width + 'px';
            pagesDiv.style.height = canvas.height + 'px';

            // other pages to wait for if first page
            var pagePromises = [];

            // render all other pages
            for (i = 2; i <= pdfDoc.numPages; i++)
                pagePromises.push(renderPage(i));

            Promise.all(pagePromises);
        }

        // Update page counters
        document.getElementById('page_num').textContent = num;

        var ctx = canvas.getContext('2d');

        // Render PDF page into canvas context
        var renderTask = page.render({
            canvasContext: ctx,
            viewport: viewport
        });

        // Wait for rendering to finish
        await renderTask.promise;

        // render the text layer
        var textContent = await page.getTextContent();
        pdfjsLib.renderTextLayer({
            textContentSource: textContent,
            container: textLayer,
            viewport: viewport,
            textDivs: []
        });

        // render the annotation layer
        var annotations = await page.getAnnotations();
        new pdfjsLib.AnnotationLayer({
            div: annotationLayer,
            viewport: viewport,
            page: page,
        }).render({
            annotations: annotations
        });

        // page 1 already has every other page rendered in above code
        if (num == 1) {
            // change selection event, set after document has been fully rendered
            document.onmouseup = async function () {
                var isHighlighting = await DotNet.invokeMethodAsync('PeerReviewWebsite', 'IsHighlighting');
                if (!isHighlighting)
                    return;

                var highlight = await updatePdfWithHighlight(Data, pdfDoc, scale);
                if (highlight === false)
                    return;

                await DotNet.invokeMethodAsync('PeerReviewWebsite', 'SetHighlight', highlight.text, highlight.page, highlight.rects);
            }

            if (highlight !== null && highlight.scrollToPage) {
                var pageDiv = document.querySelector(`.page[pageNum='${highlight.page}']`);
                pageDiv.scrollIntoView({ behavior: "smooth", block: "nearest" });
            }
        }
    }

    async function startRender(data) {
        var pdfDoc_ = await pdfjsLib.getDocument({ data: data }).promise;
        pdfDoc = pdfDoc_;
        document.getElementById('page_count').textContent = pdfDoc.numPages;

        renderPage(1);
    }

    if (highlight !== null) {
        var unmodified = await pdfjsLib.getDocument({ data: pdfData }).promise;
        var data = await unmodified.getData()
        var annotFactory = new pdfAnnotate.AnnotationFactory(data);

        highlight.rects.forEach(function (rect) {
            annotFactory.createHighlightAnnotation({
                page: highlight.page - 1,
                rect: rect,
                contents: "this is a content",
                author: "this is an author",
                color: { r: 255, g: 200, b: 0 },
                opacity: 0.5
            });
        });

        startRender(annotFactory.write());
    }
    else
        startRender(pdfData);
}

async function renderTxtDoc(text, highlight = null) {
    var pagesDiv = document.getElementById('pagesDiv'),
        txtDiv = document.getElementById('txtDiv');

    pagesDiv.hidden = true;
    txtDiv.hidden = false;

    txtDiv.innerHTML = '';
    txtDiv.innerText = text;

    if (highlight !== null) {
        highlight.rects.forEach(function (rect) {
            var highlight = document.createElement('div');

            highlight.style.position = 'absolute';
            highlight.style.left = rect[0] + 'px';
            highlight.style.top = rect[1] + 'px';
            highlight.style.width = Math.abs(rect[2] - rect[0]) + 'px';
            highlight.style.height = Math.abs(rect[3] - rect[1]) + 'px';
            highlight.style.pointerEvents = 'none';
            highlight.style.backgroundColor = '#FFEE0080'

            txtDiv.appendChild(highlight);
        });
    }

    // change selection event, set after document has been fully rendered
    document.onmouseup = async function () {
        var isHighlighting = await DotNet.invokeMethodAsync('PeerReviewWebsite', 'IsHighlighting');
        if (!isHighlighting)
            return;

        var highlight = await updateTxtWithHighlight(text);
        if (highlight === false)
            return;

        await DotNet.invokeMethodAsync('PeerReviewWebsite', 'SetHighlight', highlight.text, 0, highlight.rects);
    }
}

async function updatePdfWithHighlight(data, pdfDoc, scale) {
    var selection = window.getSelection();
    var text = selection.toString();
    // if selection is empty then don't update selection
    if (text == "")
        return false;

    var selectionPage = selection.anchorNode.parentNode.parentNode.parentNode;
    // return if not selecting text within a page
    if (!selectionPage.classList.contains('page'))
        return false;

    var pageNum = parseInt(selectionPage.getAttribute('pageNum'));
    var page = await pdfDoc.getPage(pageNum);
    var viewport = page.getViewport({ scale: scale });
    var pageRect = selectionPage.getClientRects()[0];
    var selectionRects = Array.from(selection.getRangeAt(0).getClientRects());
    var pdfRects = selectionRects.map(function (rect) {
        return viewport.convertToPdfPoint(rect.left - pageRect.x, rect.top - pageRect.y)
            .concat(viewport.convertToPdfPoint(rect.right - pageRect.x, rect.bottom - pageRect.y));
    });

    // turn off event checking while page is rendering (renderDoc will turn it back on)
    document.onmouseup = null;
    renderPdfDoc(data, scale, {
        page: pageNum,
        rects: pdfRects,
        scrollToPage: false
    });

    return { text: text, page: pageNum, rects: pdfRects }
}

async function updateTxtWithHighlight(text) {
    var selection = window.getSelection();
    var selText = selection.toString();
    // if selection is empty then don't update seleciton
    if (text == "")
        return false;

    var txtDiv = selection.anchorNode.parentElement;
    if (txtDiv.id != "txtDiv")
        return false;

    var pageRect = txtDiv.getBoundingClientRect();
    var selectionRects = Array.from(selection.getRangeAt(0).getClientRects());
    var txtRects = selectionRects.map(function (rect) {
        return [rect.left - pageRect.x, rect.top - pageRect.y,
            rect.right - pageRect.x, rect.bottom - pageRect.y];
    });

    // turn off event checking while page is rendering (renderDoc will turn it back on)
    document.onmouseup = null;
    renderTxtDoc(text, {
        rects: txtRects
    });

    return { text: selText, rects: txtRects }
}
