using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;

using System.Threading.Tasks;

namespace PeerReviewWebsite.Classes.Data.Account.RoleRequest;

/// <summary>
/// Service class for managing role requests.
/// </summary>
public class RequestService
{
    private readonly WebsiteDbContext _dbContext;

    public RequestService(WebsiteDbContext dbContext)
    {
        _dbContext = dbContext;
    }

    /// <summary>
    /// Creates a new role request for a user.
    /// </summary>
    /// <param name="userId">The ID of the user making the request.</param>
    /// <param name="requestedRole">The role requested by the user.</param>
    public async Task<RoleRequest> CreateRoleRequest(RoleRequest newRequest)
    {
        TaskCompletionSource<RoleRequest> result = new();
        _dbContext.RoleRequests.Add(newRequest);
        await _dbContext.SaveChangesAsync();
        result.SetResult(newRequest);
        return await result.Task;
    }

    public Task<Role[]> GetAllRoles()
    {
        TaskCompletionSource<Role[]> roles = new();
        roles.SetResult(_dbContext.Roles.ToArray());
        return roles.Task;
    }

    /// <summary>
    /// Retrieves all pending role requests.
    /// </summary>
    /// <returns>A collection of pending role requests.</returns>
    public async Task<RoleRequest[]> GetPendingRoleRequests()
    {
        return await _dbContext.RoleRequests.Where(r => r.Status == RoleRequestStatus.Pending).AsNoTracking().ToArrayAsync();
    }

    public async Task ApproveRoleRequest(int requestId)
    {
        RoleRequest roleRequest = await _dbContext.RoleRequests.FirstOrDefaultAsync(r => r.Id == requestId);
        if (roleRequest == null)
            return;

        User requestUser = await _dbContext.Users.FirstOrDefaultAsync(u => u.Id == roleRequest.UserId);
        if (requestUser is null)
            return;

        roleRequest.Status = RoleRequestStatus.Approved;
        _dbContext.RoleRequests.Update(roleRequest);
        requestUser.Roles.Add(roleRequest.RequestedRole);
        _dbContext.Users.Update(requestUser);
        _dbContext.SaveChanges();
    }

    public async Task<Role[]> GetRequestedRoles(int userId)
    {
        List<RoleRequest> requests = await _dbContext.RoleRequests
            .Where(r => r.UserId == userId && r.Status == RoleRequestStatus.Pending)
            .ToListAsync();

        return requests.Select(r => _dbContext.Roles.FirstOrDefault(role => role.Id == r.RequestedRole))
            .ToArray();
    }

    public async Task DenyRoleRequest(int requestId)
    {
        var roleRequest = await _dbContext.RoleRequests.FindAsync(requestId);
        if (roleRequest != null)
        {
            roleRequest.Status = RoleRequestStatus.Denied;
            await _dbContext.SaveChangesAsync();
        }
    }
}
