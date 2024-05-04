using System.Collections.Generic;

namespace PeerReviewWebsite.Classes.Data.Review {
    public class Document
    {
        public int Id { get; set; }
        public DocumentStatus Status { get; set; } = DocumentStatus.Uploaded;
        public int Author { get; set; }
        public HashSet<int> Comments { get; set; } = [];
        public HashSet<int> Updates { get; set; } = [];
        public string Title { get; set; }
        public string AdditionalNotes { get; set; }
        public HashSet<int> DocReviewers { get; set; } = [];
        public HashSet<int> DocModerators { get; set; } = [];
        public HashSet<int> RequestedClosed { get; set; } = [];

        /// <summary>
        /// The default constructor
        /// </summary>
        public Document() { }

        /// Initializes a new instance with the values of the other given <see cref="Document"/>
        /// </summary>
        /// <param name="copy">The other instance with the values to initialize with</param>
        public Document(Document copy)
        {
            Id = copy.Id;
            Status = copy.Status;
            Author = copy.Author;
            Comments.UnionWith(copy.Comments);
            Updates.UnionWith(copy.Updates);
            Title = copy.Title;
            AdditionalNotes = copy.AdditionalNotes;
            DocReviewers.UnionWith(copy.DocReviewers);
            DocModerators.UnionWith(copy.DocModerators);
            RequestedClosed.UnionWith(copy.RequestedClosed);
        }
    }

    public enum DocumentStatus
    {
        Uploaded,
        Denied,
        Approved,
        RequestClose,
        Closed,
        MovedToTrash,
        Deleted,
        Terminated
    }
}
