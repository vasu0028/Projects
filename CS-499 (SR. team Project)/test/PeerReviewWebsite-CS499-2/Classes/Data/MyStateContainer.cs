using PeerReviewWebsite.Classes.Data.Account;
using PeerReviewWebsite.Classes.Data.Review;
using System.Collections.Generic;

namespace PeerReviewWebsite.Classes.Data {

    // <summary>
    // Current state of the program
    // <summary>
    public class MyStateContainer {
        public User User { get; set; }
        // Used for going to other users' profiles
        public User VisitingUser { get; set; }
        public Document CurrentDoc { get; set; }
        public DocumentUpdate DocumentUpdateToDownload { get; set; }
        public HashSet<int> UploadedDocs { get; set; } = [];
        public HashSet<int> UserIds { get; set; } = [];
        public HashSet<int> RoleIds { get; set; } = [];
    }
}