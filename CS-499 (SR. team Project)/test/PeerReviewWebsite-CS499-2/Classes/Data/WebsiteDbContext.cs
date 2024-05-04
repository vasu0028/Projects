using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using PeerReviewWebsite.Classes.Data.Account;
using PeerReviewWebsite.Classes.Data.Account.RoleRequest;
using PeerReviewWebsite.Classes.Data.Review;
using System;
using System.Collections.Generic;
using System.Linq;

namespace PeerReviewWebsite.Classes.Data {
    /// <summary>
    /// Represents the entirety of the websites database
    /// </summary>
    public class WebsiteDbContext(DbContextOptions options) : DbContext(options) {
        /// <summary>
        /// The users in the database
        /// </summary>
        public DbSet<User> Users { get; set; }

        /// <summary>
        /// The roles in the database
        /// </summary>
        public DbSet<Role> Roles { get; set; }

        /// <summary>
        /// The documents in the database
        /// </summary>
        public DbSet<RoleRequest> RoleRequests { get; set; }

        /// <summary>
        /// The roles in the database
        /// </summary>
        public DbSet<Document> Documents { get; set; }

        /// <summary>
        /// The comments in the database
        /// </summary>
        public DbSet<Comment> Comments { get; set; }

        /// <summary>
        /// The updates to the documents in the database
        /// </summary>
        public DbSet<DocumentUpdate> DocumentUpdates { get; set; }

        static string IdsToString(HashSet<int> ids) => string.Join(',', ids);

        static HashSet<int> StringToIds(string str) {
            string[] isStrings = str.Split(',');
            IEnumerable<int> ids = isStrings.Select(idString => int.TryParse(idString, out int id) ? (int?)id : null)
                .Where(id => id is not null)
                .Select(id => id.Value);
            return new(ids);
        }

        static string RectsToString(float[][] rects) => string.Join('|', rects.Select(rect => string.Join(',', rect)));

        static float[][] StringToRects(string str) {
            string[][] rectStrings = str.Split('|').Select(rectStr => rectStr.Split(',')).ToArray();
            return rectStrings.Select(rectStr => rectStr.Select(coordStr => float.TryParse(coordStr, out float coord) ? (float?)coord : null)
                .Where(coord => coord is not null)
                .Select(coord => coord.Value)
                .ToArray()
            ).ToArray();
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder) {
            ValueConverter<HashSet<int>, string> idsAsString = new(
                ids => IdsToString(ids),
                str => StringToIds(str));
            ValueComparer<HashSet<int>> idsComparer = new(true);

            ValueConverter<float[][], string> rectsAsString = new(
                rects => RectsToString(rects),
                str => StringToRects(str));
            ValueComparer<float[][]> rectsComparer = new(true);

            // Add the Users table
            modelBuilder.Entity<User>(entity => {
                entity.ToTable("Users");
                entity.HasKey(user => user.Id);
                entity.Property(user => user.FirstName);
                entity.Property(user => user.LastName);
                entity.Property(user => user.Email);
                entity.Property(user => user.Password);
                entity.Property(user => user.Roles).HasConversion(idsAsString, idsComparer);
                entity.Property(user => user.OwnedDocuments).HasConversion(idsAsString, idsComparer);
                entity.Property(user => user.OwnedComments).HasConversion(idsAsString, idsComparer);
            });

            // Add the Roles table
            modelBuilder.Entity<Role>(entity => {
                entity.ToTable("Roles");
                entity.HasKey(role => role.Id);
                entity.Property(role => role.Name);
                entity.Property(role => role.Permissions);
            });

            // Add rolerequest table
            modelBuilder.Entity<RoleRequest>(entity =>
            {
                entity.ToTable("RoleRequests");
                entity.HasKey(r => r.Id);
                entity.Property(r => r.UserId);
                entity.Property(r => r.Status);
                entity.Property(r => r.RequestedRole); // this line to include the RequestedRole property
            });

            // Add the Documents table
            modelBuilder.Entity<Document>(entity => {
                entity.ToTable("Documents");
                entity.HasKey(doc => doc.Id);
                entity.Property(doc => doc.Status);
                entity.Property(doc => doc.Author);
                entity.Property(doc => doc.Comments).HasConversion(idsAsString, idsComparer);
                entity.Property(doc => doc.Updates).HasConversion(idsAsString, idsComparer);
                entity.Property(doc => doc.Title);
                entity.Property(doc => doc.AdditionalNotes);
                entity.Property(doc => doc.DocReviewers).HasConversion(idsAsString, idsComparer);
                entity.Property(doc => doc.DocModerators).HasConversion(idsAsString, idsComparer);
                entity.Property(doc => doc.RequestedClosed).HasConversion(idsAsString, idsComparer);
            });

            // Add the Comments table
            modelBuilder.Entity<Comment>(entity => {
                entity.ToTable("Comments");
                entity.HasKey(comment => comment.Id);
                entity.Property(comment => comment.Status);
                entity.Property(comment => comment.Author);
                entity.Property(comment => comment.Document);
                entity.Property(comment => comment.Content);
                entity.Property(comment => comment.UploadDate);
                entity.Property(comment => comment.DocumentUpdate);
                entity.Property(comment => comment.NeedsResolving);
                entity.Property(comment => comment.HasHighlight);
                entity.Property(comment => comment.HighlightText);
                entity.Property(comment => comment.HighlightPage);
                entity.Property(comment => comment.HighlightRects).HasConversion(rectsAsString, rectsComparer);
            });

            // Add the Document Updates table
            modelBuilder.Entity<DocumentUpdate>(entity => {
                entity.ToTable("DocumentUpdates");
                entity.HasKey(update => update.Id);
                entity.Property(update => update.FileName);
                entity.Property(update => update.Content);
                entity.Property(update => update.Description);
                entity.Property(update => update.UploadDate);
                entity.Property(update => update.IsInitial);
            });
        }
    }
}
