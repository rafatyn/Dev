// Data/AppDbContext.cs

using CRTApp.Models;
using Microsoft.EntityFrameworkCore;
using Path = CRTApp.Models.Path;

namespace CRTApp.Data
{
    public class AppDbContext: DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
        }

        public DbSet<User> User { get; set; }
        public DbSet<UserLogin> UserLogin { get; set; }
        public DbSet<UserSession> UserSession { get; set; }
        public DbSet<Path> Path { get; set; }
        public DbSet<Place> Place { get; set; }
        public DbSet<PathPlace> PathPlace { get; set; }
        public DbSet<Product> Product { get; set; }
        public DbSet<UserVote> UserVote { get; set; }
        public DbSet<UserBookmark> UserBookmark { get; set; }
    }
}