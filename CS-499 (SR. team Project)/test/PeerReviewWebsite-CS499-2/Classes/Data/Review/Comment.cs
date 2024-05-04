using System;

namespace PeerReviewWebsite.Classes.Data.Review {
    public class Comment : IReviewItem {
        public int Id { get; set; }
        public CommentStatus Status { get; set; }
        public int Author { get; set; }
        public int Document { get; set; }
        public string Content { get; set; }
        public DateTime UploadDate { get; set; }
        public int DocumentUpdate { get; set; }
        public bool NeedsResolving { get; set; }

        public bool HasHighlight { get; set; }
        public string HighlightText { get; set; }
        public int HighlightPage { get; set; }
        public float[][] HighlightRects { get; set; }

        /// <summary>
        /// The default constructor
        /// </summary>
        public Comment() { }

        /// Initializes a new instance with the values of the other given <see cref="Comment"/>
        /// </summary>
        /// <param name="copy">The other instance with the values to initialize with</param>
        public Comment(Comment copy) {
            Id = copy.Id;
            Status = copy.Status;
            Author = copy.Author;
            Document = copy.Document;
            Content = copy.Content;
            UploadDate = copy.UploadDate;
            DocumentUpdate = copy.DocumentUpdate;
            NeedsResolving = copy.NeedsResolving;
            HasHighlight = copy.HasHighlight;
            HighlightText = copy.HighlightText;
            HighlightPage = copy.HighlightPage;
            HighlightRects = copy.HighlightRects;
        }
    }

    public enum CommentStatus {
        Uploaded,
        Approved,
        Resolved
    }
}
