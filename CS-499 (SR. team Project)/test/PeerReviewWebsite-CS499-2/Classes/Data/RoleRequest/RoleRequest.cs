using System;

namespace PeerReviewWebsite.Classes.Data.Account.RoleRequest
{
    public class RoleRequest
    {
        public int Id { get; set; }
        public int UserId { get; set; }
        public RoleRequestStatus Status { get; set; } // pending, approved, rejected
        public int RequestedRole { get; set; } // The role requested by the user
        public bool ApproveByModerator { get; set; } // Indicates if the request is approved by a moderator
        public RoleRequest() { }

        public RoleRequest(RoleRequest copy)
        {
            Id = copy.Id;
            UserId = copy.UserId;
            Status = copy.Status;
            RequestedRole = copy.RequestedRole;
            ApproveByModerator = copy.ApproveByModerator;
        }
    }

    public enum RoleRequestStatus {
        Pending,
        Approved,
        Denied
    }
}
