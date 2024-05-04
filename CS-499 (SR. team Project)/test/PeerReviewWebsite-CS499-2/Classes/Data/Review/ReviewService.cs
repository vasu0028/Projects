using Microsoft.EntityFrameworkCore;
using System.Linq;
using System.Threading.Tasks;

namespace PeerReviewWebsite.Classes.Data.Review {

    public class ReviewService(WebsiteDbContext context) {
        /// <summary>
        /// Gets the <see cref="Document"/> with the given id
        /// </summary>
        /// <param name="id">The id of the <see cref="Document"/></param>
        /// <returns>The <see cref="Document"/> with the id if it exists, <see langword="null"/> otherwise</returns>
        public async Task<Document> GetDocumentAsync(int id) =>
            await context.Documents.Where(doc => doc.Id == id).AsNoTracking().FirstOrDefaultAsync();

        public async Task<Document[]> GetAllDocumentsAsync() =>
            await context.Documents.AsNoTracking().ToArrayAsync();

        /// <summary>
        /// Adds the <see cref="Document"/>
        /// </summary>
        /// <param name="doc">The object representation</param>
        /// <returns>The added <see cref="Document"/></returns>
        public Task<Document> CreateDocumentAsync(Document doc) {
            TaskCompletionSource<Document> result = new();
            context.Documents.Add(doc);
            context.SaveChanges();
            Document addedDoc = new(doc);
            result.SetResult(addedDoc);
            return result.Task;
        }

        /// <summary>
        /// Gets the <see cref="Comment"/> with the given id
        /// </summary>
        /// <param name="id">The id of the <see cref="Comment"/></param>
        /// <returns>The <see cref="Comment"/> with the id if it exists, <see langword="null"/> otherwise</returns>
        public async Task<Comment> GetCommentAsync(int id) =>
            await context.Comments.Where(com => com.Id == id).AsNoTracking().FirstOrDefaultAsync();

        /// <summary>
        /// Adds the <see cref="Comment"/>
        /// </summary>
        /// <param name="com">The object representation</param>
        /// <returns>The added <see cref="Comment"/></returns>
        public Task<Comment> CreateCommentAsync(Comment com) {
            TaskCompletionSource<Comment> result = new();
            context.Comments.Add(com);
            context.SaveChanges();
            Comment addedComment = new(com);
            result.SetResult(addedComment);
            return result.Task;
        }

        /// <summary>
        /// Gets the <see cref="DocumentUpdate"/> with the given id
        /// </summary>
        /// <param name="id">The id of the <see cref="DocumentUpdate"/></param>
        /// <returns>The <see cref="DocumentUpdate"/> with the id if it exists, <see langword="null"/> otherwise</returns>
        public async Task<DocumentUpdate> GetDocumentUpdateAsync(int id) =>
            await context.DocumentUpdates.Where(upd => upd.Id == id).AsNoTracking().FirstOrDefaultAsync();

        public Task<DocumentUpdate> CreateDocumentUpdateAsync(DocumentUpdate upd) {
            TaskCompletionSource<DocumentUpdate> result = new();
            context.DocumentUpdates.Add(upd);
            context.SaveChanges();
            DocumentUpdate addedUpd = new(upd);
            result.SetResult(addedUpd);
            return result.Task;
        }
    }
}
