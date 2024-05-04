using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using PeerReviewWebsite.Classes.Data;
using PeerReviewWebsite.Classes.Data.Account;
using PeerReviewWebsite.Classes.Data.Account.RoleRequest;
using PeerReviewWebsite.Classes.Data.Review;
using System;
using System.Runtime.InteropServices;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddRazorPages();
builder.Services.AddServerSideBlazor();
builder.Services.AddSingleton<MyStateContainer>();

// Add connections
string connectionString = null;
if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
    connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
    connectionString = builder.Configuration.GetConnectionString("LinuxConnection");

if (connectionString is null)
    throw new InvalidOperationException("Connection string 'DefaultConnection' not found.");

builder.Services.AddDbContext<WebsiteDbContext>(options => options.UseSqlServer(connectionString));

// Add services
builder.Services.AddScoped<AccountService>();
builder.Services.AddScoped<ReviewService>();
builder.Services.AddScoped<RequestService>();

var app = builder.Build();
var state = app.Services.GetService<MyStateContainer>();
if (!app.Environment.IsDevelopment()) {
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();

app.UseStaticFiles();

app.UseRouting();

app.MapBlazorHub();
app.MapFallbackToPage("/_Host");

// Ensure database is created
// TODO: Possibly move to migrations when coming to release
using IServiceScope scope = app.Services.CreateScope();
WebsiteDbContext dbContext = scope.ServiceProvider.GetRequiredService<WebsiteDbContext>();
#if DEBUG
dbContext.Database.EnsureDeleted();
#endif
dbContext.Database.EnsureCreated();

AccountService accountService = new(dbContext);

// Add admin account
string adminEmail = "admin";
if (await accountService.GetUserAsync(adminEmail) is null)
{
    // Add admin role
    string adminRoleName = "Administrator";
    Role adminRole = await accountService.GetRoleAsync(adminRoleName);
    adminRole ??= await accountService.CreateRoleAsync(new Role
    {
        Name = adminRoleName,
        Permissions = Permission.All
    });
    state.RoleIds.Add(adminRole.Id);

    User adminAccount = await accountService.CreateUserAsync(new User
    {
        FirstName = "Admin",
        LastName = "User",
        Email = adminEmail,
        Password = "admin123"
    });
    state.UserIds.Add(adminAccount.Id);
    // Add admin role to admin account
    await accountService.AddRoleToUserAsync(adminAccount, adminRole);
}

// Add author account
string authorEmail = "author";
if (await accountService.GetUserAsync(authorEmail) is null)
{
    // Add author role
    string authorRoleName = "Author";
    Role authorRole = await accountService.GetRoleAsync(authorRoleName);
    authorRole ??= await accountService.CreateRoleAsync(new Role
    {
        Name = authorRoleName,
        Permissions = Permission.UploadDocument | Permission.UpdateDocument | Permission.Comment | Permission.Respond | Permission.RequestClose
    });
    state.RoleIds.Add(authorRole.Id);

    User authorAccount = await accountService.CreateUserAsync(new User
    {
        FirstName = "Author",
        LastName = "User",
        Email = authorEmail,
        Password = "author123"
    });
    state.UserIds.Add(authorAccount.Id);

    // Add author role to author account
    await accountService.AddRoleToUserAsync(authorAccount, authorRole);
}

// Add reviewer role
string reviewerRoleName = "Reviewer";
Role reviewerRole = await accountService.GetRoleAsync(reviewerRoleName);
reviewerRole ??= await accountService.CreateRoleAsync(new Role
{
    Name = reviewerRoleName,
    Permissions = Permission.ReviewDocument | Permission.Comment | Permission.Respond | Permission.RequestClose
});
state.RoleIds.Add(reviewerRole.Id);

// Add reviewer account
string reviewerEmail = "reviewer";
if (await accountService.GetUserAsync(reviewerEmail) is null)
{


    User reviewerAccount = await accountService.CreateUserAsync(new User
    {
        FirstName = "Reviewer",
        LastName = "User",
        Email = reviewerEmail,
        Password = "reviewer123"
    });
    state.UserIds.Add(reviewerAccount.Id);

    // Add reviewer role to reviewer account
    await accountService.AddRoleToUserAsync(reviewerAccount, reviewerRole);
}


// Add second reviewer account
string email = "reviewer2";
if (await accountService.GetUserAsync(email) is null)
{

    User reviewerAccount = await accountService.CreateUserAsync(new User
    {
        FirstName = "Reviewer2",
        LastName = "User",
        Email = email,
        Password = "reviewer123"
    });
    state.UserIds.Add(reviewerAccount.Id);

    // Add reviewer role to reviewer account
    await accountService.AddRoleToUserAsync(reviewerAccount, reviewerRole);
}

// Add Customer role
string customerRoleName = "Customer";
Role customerRole = await accountService.GetRoleAsync(customerRoleName);
customerRole ??= await accountService.CreateRoleAsync(new Role
{
    Name = customerRoleName,
    Permissions = Permission.ReadOnly
});
state.RoleIds.Add(customerRole.Id);

// Add Moderator role
string moderatorRoleName = "Moderator";
Role moderatorRole = await accountService.GetRoleAsync(moderatorRoleName);
moderatorRole ??= await accountService.CreateRoleAsync(new Role
{
    Name = moderatorRoleName,
    Permissions = Permission.ApproveDocument | Permission.SelectReviewer | Permission.CloseDocument | Permission.EditRoles
});
state.RoleIds.Add(moderatorRole.Id);

app.Run();