using System;
using System.ComponentModel.DataAnnotations.Schema;
using System.IO;

namespace PeerReviewWebsite.Classes.Data.Review {
    public class DocumentUpdate : IReviewItem {
        public int Id { get; set; }
        public string FileName { get; set; }
        public byte[] Content { get; set; }
        public string Description { get; set; }
        public DateTime UploadDate { get; set; }
        public bool IsInitial { get; set; } = false;

        // Helper property
        [NotMapped]
        public string FileType => Path.GetExtension(FileName).ToLower();

        /// <summary>
        /// Default constructor
        /// </summary>
        public DocumentUpdate() { }

        public DocumentUpdate(DocumentUpdate copy) {
            Id = copy.Id;
            FileName = copy.FileName;
            Content = copy.Content;
            Content = copy.Content;
            UploadDate = copy.UploadDate;
            Description = copy.Description;
            IsInitial = copy.IsInitial;
        }
    }
}
