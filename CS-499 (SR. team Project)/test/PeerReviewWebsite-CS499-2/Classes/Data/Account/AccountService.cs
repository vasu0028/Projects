using Microsoft.EntityFrameworkCore;
using System;
using System.Linq;
using System.Reflection.Metadata;
using System.Threading.Tasks;
using PeerReviewWebsite.Classes.Data.Review;
using Document = PeerReviewWebsite.Classes.Data.Review.Document;
using System.Collections.Generic;

namespace PeerReviewWebsite.Classes.Data.Account {
    /// <summary>
    /// A helper class that allows for retrieval and manipulation of <see cref="User"/> accounts
    /// </summary>
    /// <param name="context">The database context for the website</param>
    public class AccountService(WebsiteDbContext context) {
        /// <summary>
        /// Gets the <see cref="User"/> with the given username
        /// </summary>
        /// <param name="id">The id if the <see cref="User"/></param>
        /// <returns>The <see cref="User"/> with the given id, <see langword="null"/> if not found</returns>
        public async Task<User> GetUserAsync(int id) =>
            await context.Users.Where(user => user.Id == id).AsNoTracking().FirstOrDefaultAsync();

        /// <summary>
        /// Gets the <see cref="User"/> with the given username
        /// </summary>
        /// <param name="email">The username of the <see cref="User"/></param>
        /// <returns>The <see cref="User"/> with the given username, <see langword="null"/> if not found</returns>
        public async Task<User> GetUserAsync(string email) =>
            await context.Users.Where(user => user.Email == email).AsNoTracking().FirstOrDefaultAsync();

        public async Task<User[]> GetAllUsersAsync() =>
            await context.Users.AsNoTracking().ToArrayAsync();

        /// <summary>
        /// Adds the <see cref="User"/> account
        /// </summary>
        /// <param name="user">The object representation</param>
        /// <returns>The added <see cref="User"/></returns>
        public Task<User> CreateUserAsync(User user)
        {
            TaskCompletionSource<User> result = new();
            context.Users.Add(user);
            context.SaveChanges();
            User addedUser = new(user);
            result.SetResult(addedUser);
            return result.Task;
        }

        /// <summary>
        /// Removes the user from the database
        /// </summary>
        /// <param name="user">The user to purge</param>
        /// <returns>True if the user was found and deleted, false otherwise</returns>
        public async Task<bool> DeleteUserAsync(User user)
        {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return false;

            context.Users.Remove(dbUser);
            context.SaveChanges();
            return true;
        }

        /// <summary>
        /// Gets the <see cref="Role"/> with the given id
        /// </summary>
        /// <param name="id">The id of the <see cref="Role"/></param>
        /// <returns>The <see cref="Role"/> with the given id, <see langword="null"/> if not found</returns>
        public async Task<Role> GetRoleAsync(int id) =>
            await context.Roles.Where(role => role.Id == id).AsNoTracking().FirstOrDefaultAsync();

        /// <summary>
        /// Gets the <see cref="Role"/> with the given name
        /// </summary>
        /// <param name="name">The namde of the <see cref="Role"/></param>
        /// <returns>The <see cref="Role"/> with the given name, <see langword="null"/> if not found</returns>
        public async Task<Role> GetRoleAsync(string name) =>
            await context.Roles.Where(role => role.Name == name).AsNoTracking().FirstOrDefaultAsync();

        /// <summary>
        /// Adds the <see cref="Role"/>
        /// </summary>
        /// <param name="role">The object representation</param>
        /// <returns>The added <see cref="Role"/></returns>
        public Task<Role> CreateRoleAsync(Role role) {
            TaskCompletionSource<Role> result = new();
            context.Roles.Add(role);
            context.SaveChanges();
            Role addedRole = new(role);
            result.SetResult(addedRole);
            return result.Task;
        }

        /// <summary>
        /// Gets every role that the user has
        /// </summary>
        /// <param name="user">The user to get from</param>
        /// <returns>An array of roles corresponding to the roles that the user has</returns>
        public async Task<Role[]> GetUserRolesAsync(User user) {
            List<Role> roles = new();
            foreach (int roleId in user.Roles)
                roles.Add(await GetRoleAsync(roleId));
            return roles.ToArray();
        }

        /// <summary>
        /// Gets the combined <see cref="Permission"/>s that the <see cref="User"/> has
        /// </summary>
        /// <param name="user">The <see cref="User"/> to get the <see cref="Permission"/>s from</param>
        /// <returns>The combined <see cref="Permission"/>s of the <see cref="User"/></returns>
        public async Task<Permission> GetUserPermissions(User user) {
            Permission result = Permission.None;


            //Checks if user is null, if so then breaks out of loop to boot user to error page
            if (user == null)
            {
                return Permission.None;
            }

            foreach (int roleId in user.Roles) {
                Role role = await GetRoleAsync(roleId);
                result |= role.Permissions;
            }

            return result;
        }

        /// <summary>
        /// Changes the given <see cref="Role"/>'s permissions with the given <see cref="Permission"/>s
        /// </summary>
        /// <param name="role">The <see cref="Role"/> will get new <see cref="Permission"/>s from</param>
        /// <returns>Returns true if attempt was unsuccessful, false otherwise</returns>
        public async Task<bool> ChangeRolePermissions(Role role, Permission permissions)
        {
            Role dbRole = await context.Roles.Where(r => r.Id == role.Id).FirstOrDefaultAsync();
            if (dbRole == null)
                return true;

            dbRole.Permissions = permissions;
            context.Roles.Update(dbRole);
            context.SaveChanges();
            return false;
        }

        /// <summary>
        /// Removes <see cref="Role"/> from the database
        /// </summary>
        /// <param name="role">The <see cref="Role"/> will be removed</param>
        /// <returns>Returns false if attempt was unsuccessful, true otherwise</returns>
        public async Task<bool> DeleteRole(Role role)
        {
            Role dbRole = await context.Roles.Where(r => r.Id == role.Id).FirstOrDefaultAsync();
            if (dbRole == null)
                return false;

            context.Roles.Remove(dbRole);
            context.SaveChanges();
            return true;
        }

        /// <summary>
        /// Removes <see cref="Role"/> from the  <see cref="User"/> 
        /// </summary>
        /// <param name="role">The <see cref="Role"/> will be removed from <see cref="User"/>'s account</param>
        /// <returns>Returns new <see cref="User"/> if attempt was unsuccessful, original <see cref="User"/> otherwise</returns>
        public async Task<User> RemoveRoleFromUser(User user, Role role)
        {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return user;

            dbUser.Roles.Remove(role.Id);
            context.Users.Update(dbUser);
            context.SaveChanges();
            return new(dbUser);
        }

        /// <summary>
        /// Adds the given <see cref="Role"/> to the given <see cref="User"/>
        /// </summary>
        /// <param name="user">The <see cref="User"/> to add the <see cref="Role"/> to</param>
        /// <param name="role">The <see cref="Role"/> to add to the <see cref="User"/></param>
        /// <returns>The new state if the role was added or already added, the old state otherwise</returns>
        public async Task<User> AddRoleToUserAsync(User user, Role role) {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return user;

            dbUser.Roles.Add(role.Id);
            context.Users.Update(dbUser);
            context.SaveChanges();
            return new(dbUser);
        }

        /// <summary>
        /// Gets if the <see cref="Role"/> has any of the given <see cref="Permission"/>s
        /// </summary>
        /// <param name="role">The <see cref="Role"/> to check against</param>
        /// <param name="permissions">The <see cref="Permission"/>s to check against</param>
        /// <returns><see langword="true"/> if the <see cref="Role"/> has any given <see cref="Permission"/>, <see langword="false"/> otherwise</returns>
        public async Task<bool> DoesRoleHavePermission(Role role, Permission permissions)
        {
            Role dbRole = await GetRoleAsync(role.Id);
            return (dbRole.Permissions & permissions) != Permission.None;
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has all of the given <see cref="Permission"/>s
        /// </summary>
        /// <param name="user">The <see cref="User"/> to check against</param>
        /// <param name="permissions">The <see cref="Permission"/>s to check against</param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has every given <see cref="Permission"/>, <see langword="false"/> otherwise</returns>
        public async Task<bool> UserHasPermissions(User user, Permission permissions) {
            Permission userPerms = await GetUserPermissions(user);

            return (userPerms & permissions) == permissions;
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has any of the given <see cref="Permission"/>s
        /// </summary>
        /// <param name="user">The <see cref="User"/> to check against</param>
        /// <param name="permissions">The <see cref="Permission"/>s to check against</param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has any given <see cref="Permission"/>, <see langword="false"/> otherwise</returns>
        public async Task<bool> UserHasAnyPermissions(User user, Permission permissions) {
            Permission userPerms = await GetUserPermissions(user);

            return (userPerms & permissions) != Permission.None;
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has all <see cref="Permission"/>s
        /// </summary>
        /// <param name="user">The given <see cref="User"/> to check against</param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has any of the right <see cref="Permission"/>s, <see langword="false"/> otherwise</returns>
        public async Task<bool> UserIsAdmin(User user)
        {
            return await UserHasAnyPermissions(user, Permission.All);
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has any <see cref="Permission"/> that would give them access to the moderator tab
        /// </summary>
        /// <param name="user">The given <see cref="User"/> to check against</param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has any of the right <see cref="Permission"/>s, <see langword="false"/> otherwise</returns>
        public async Task<bool> UserIsModerator(User user)
        {
            return await UserHasAnyPermissions(user, Permission.ApproveDocument |
                                                     Permission.CloseDocument |
                                                     Permission.SelectReviewer |
                                                     Permission.ManageUsers |
                                                     Permission.EditPermissions);
        }

        public async Task<bool> UserIsDocumentModerator(User user) {
            return await UserHasAnyPermissions(user, Permission.ApproveDocument |
                                                     Permission.CloseDocument |
                                                     Permission.SelectReviewer);
        }

        public async Task<bool> UserIsUserModerator(User user) {
            return await UserHasAnyPermissions(user, Permission.ManageUsers |
                                                     Permission.EditPermissions);
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has any <see cref="Permission"/> to review documents
        /// </summary>
        /// <param name="user">The given <see cref="User"/> to check against</param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has any of the right <see cref="Permission"/>s, <see langword="false"/> otherwise</returns>
        public async Task<bool> UserIsReviewer(User user)
        {
            return await UserHasAnyPermissions(user, Permission.ReviewDocument);
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has any <see cref="Permission"/> to upload documents
        /// </summary>
        /// <param name="user">The given <see cref="User"/> to check against</param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has any of the right <see cref="Permission"/>s, <see langword="false"/> otherwise</returns>
        public async Task<bool> UserIsAuthor(User user)
        {
            return await UserHasAnyPermissions(user, Permission.UploadDocument | Permission.UpdateDocument);
        }

        /// <summary>
        /// Gets if the <see cref="User"/> has the given <see cref="Permission"/> 
        /// </summary>
        /// <param name="user">The given <see cref="User"/> to check</param>
        /// <param name="permission"> The <see cref="Permission"/> to check if the User has it </param>
        /// <returns><see langword="true"/> if the <see cref="User"/> has any of the right <see cref="Permission"/>s, <see
        public async Task<bool> DoesUserHavePermission(User user, Permission permission)
        {
            return await UserHasAnyPermissions(user, permission);
        }

        /// <summary>
        /// Adds the given <see cref="Document"/> to the given <see cref="User"/>
        /// </summary>
        /// <param name="user">The <see cref="User"/> to add the <see cref="Document"/> to</param>
        /// <param name="doc">The <see cref="Document"/> to add to the <see cref="User"/></param>
        /// <returns>The new <see cref="User"/> state if successful, the old state otherwise</returns>
        public async Task<User> AddDocumentToUserAsync(User user, Document doc) {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return user;

            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return user;

            dbUser.OwnedDocuments.Add(dbDoc.Id);
            context.Users.Update(dbUser);
            dbDoc.Author = dbUser.Id;
            context.Documents.Update(dbDoc);
            context.SaveChanges();
            return new(dbUser);
        }

        /// <summary>
        /// Adds the given <see cref="Comment"/> to the given <see cref="Document"/>, as well as the given <see cref="User"/>
        /// </summary>
        /// <param name="user">The <see cref="User"/> to add the <see cref="Comment"/> to</param>
        /// <param name="doc">The <see cref="Document"/> to add the <see cref="Comment"/> to</param>
        /// <param name="comment">The <see cref="Comment"/> to add the the to <see cref="User"/> and <see cref="Document"/></param>
        /// <returns>The new <see cref="User"/> and <see cref="Document"/> state if successful, the old state otherwise</returns>
        public async Task<(User, Document)> AddCommentToDocumentAsync(User user, Document doc, Comment comment) {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return (user, doc);

            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return (user, doc);

            Comment dbComment = await context.Comments.Where(c => c.Id == comment.Id).FirstOrDefaultAsync();
            if (dbComment is null)
                return (user, doc);

            dbUser.OwnedComments.Add(dbComment.Id);
            context.Users.Update(dbUser);
            dbDoc.Comments.Add(dbComment.Id);
            context.Documents.Update(dbDoc);
            dbComment.Author = dbUser.Id;
            context.Comments.Update(dbComment);
            context.SaveChanges();
            return (new User(dbUser), new Document(dbDoc));
        }

        /// <summary>
        /// Adds the given <see cref="DocumentUpdate"/> to the given <see cref="Document"/>
        /// </summary>
        /// <param name="doc">The <see cref="Document"/> to add the <see cref="DocumentUpdate"/> to</param>
        /// <param name="update">The <see cref="DocumentUpdate"/> to add to the <see cref="Document"/></param>
        /// <returns>The new <see cref="Document"/> state if successful, the old state otherwise</returns>
        public async Task<Document> AddUpdateToDocumentAsync(Document doc, DocumentUpdate update) {
            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return doc;

            DocumentUpdate dbUpd = await context.DocumentUpdates.Where(u => u.Id == update.Id).FirstOrDefaultAsync();
            if (dbUpd is null)
                return doc;

            dbDoc.Updates.Add(dbUpd.Id);
            context.Documents.Update(dbDoc);
            context.SaveChanges();
            return new(dbDoc);
        }

        /// <summary>
        /// Updates the document status of the given <see cref="Document"/> 
        /// </summary>
        /// <param name="doc">The <see cref="Document"/> that holds the changes to the Document status
        /// <returns>The new <see cref="Document"/> state if successful, the old state otherwise</returns>
        public async Task<Document> ChangeDocumentStatus(Document doc)
        {
            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return doc;

            dbDoc.Status = doc.Status;
            context.Documents.Update(dbDoc);
            context.SaveChanges();
            return new Document(dbDoc);
        }

        /// <summary>
        /// Updates the comment status of the given <see cref="Comment"/>
        /// </summary>
        /// <param name="comment">The <see cref="Comment"/> that hold the changes to the comment status</param>
        /// <returns>The new <see cref="Comment"/> state if successful, the old state otherwise</returns>
        public async Task<Comment> ChangeCommentStatus(Comment comment)
        {
            Comment dbComment = await context.Comments.Where(c => c.Id == comment.Id).FirstOrDefaultAsync();
            if (dbComment is null)
                return comment;

            dbComment.Status = comment.Status;
            context.Comments.Update(dbComment);
            context.SaveChanges();
            return new Comment(dbComment);
        }

        /// <summary>
        /// Updates notes tied to the given <see cref="Document"/> 
        /// </summary>
        /// <param name="doc">The <see cref="Document"/> that has the notes to add to the new Document
        /// <returns>The new <see cref="Document"/> state if successful, the old state otherwise</returns>
        public async Task<Document> AddDocumentNotes(Document doc)
        {
            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return (doc);

            dbDoc.AdditionalNotes = doc.AdditionalNotes;
            context.Documents.Update(dbDoc);
            context.SaveChanges();
            return (new Document(dbDoc));
        }

        /// <summary>
        /// Assigns the <see cref="Document"/> to the given users
        /// </summary>
        /// <param name="doc">The <see cref="Document"/> has the ids of the reviewers and moderators
        /// <returns>The new <see cref="Document"/> state if successful, the old state otherwise</returns>
        public async Task<Document> AssignDocuments(Document doc)
        {
            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return (doc);

            dbDoc.DocReviewers = doc.DocReviewers;
            dbDoc.DocModerators = doc.DocModerators;
            context.Documents.Update(dbDoc);
            context.SaveChanges();
            return (new Document(dbDoc));
        }


        /// <summary>
        /// Notes on the <see cref="Document"/> who has requested it to be closed
        /// </summary>
        /// <param name="doc">The <see cref="Document"/> has the ids of those who have requested close
        /// <returns>The new <see cref="Document"/> state if successful, the old state otherwise</returns>
        public async Task<Document> RequestClosed(Document doc)
        {
            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc is null)
                return (doc);

            dbDoc.RequestedClosed = doc.RequestedClosed;
            context.Documents.Update(dbDoc);
            context.SaveChanges();
            return (new Document(dbDoc));
        }

        /// <summary>
        /// Removes <see cref="Document"/> from the database
        /// </summary>
        /// <param name="role">The <see cref="Document"/> will be removed</param>
        /// <returns>Returns false if attempt was unsuccessful, true otherwise</returns>
        public async Task<bool> DeleteDocument(Document doc)
        {
            Document dbDoc = await context.Documents.Where(d => d.Id == doc.Id).FirstOrDefaultAsync();
            if (dbDoc == null)
                return false;

            context.Documents.Remove(dbDoc);
            context.SaveChanges();
            return true;
        }

        /// <summary>
        /// Removes <see cref="Comment"/> from the database
        /// </summary>
        /// <param name="role">The <see cref="Comment"/> will be removed</param>
        /// <returns>Returns false if attempt was unsuccessful, true otherwise</returns>
        public async Task<bool> DeleteComment(Comment comment)
        {
            Comment dbComment = await context.Comments.Where(c => c.Id == comment.Id).FirstOrDefaultAsync();
            if (dbComment == null)
                return false;

            context.Comments.Remove(dbComment);
            context.SaveChanges();
            return true;
        }

        /// <summary>
        /// Removes Comment from the  <see cref="User"/> 
        /// </summary>
        /// <param name="commentId">The comment id will be removed from <see cref="User"/>'s account</param>
        /// <returns>Returns new <see cref="User"/> if attempt was unsuccessful, original <see cref="User"/> otherwise</returns>
        public async Task<User> RemoveCommentFromUser(User user, int commentId)
        {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return user;

            dbUser.OwnedComments.Remove(commentId);
            context.Users.Update(dbUser);
            context.SaveChanges();
            return new(dbUser);
        }

        /// <summary>
        /// Removes <see cref="Document"/>  from the  <see cref="User"/> 
        /// </summary>
        /// <param name="doc">The <see cref="Document"/>  will be removed from <see cref="User"/>'s account</param>
        /// <returns>Returns new <see cref="User"/> if attempt was unsuccessful, original <see cref="User"/> otherwise</returns>
        public async Task<User> RemoveDocFromOwner(User user, Document doc)
        {
            User dbUser = await context.Users.Where(u => u.Id == user.Id).FirstOrDefaultAsync();
            if (dbUser is null)
                return user;

            dbUser.OwnedDocuments.Remove(doc.Id);
            context.Users.Update(dbUser);
            context.SaveChanges();
            return new(dbUser);
        }
    }
}
