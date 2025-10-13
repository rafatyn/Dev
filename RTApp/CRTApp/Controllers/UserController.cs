using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using CRTApp.Data;
using CRTApp.Models;


[Route("[controller]/[action]")]
[ApiController]
public class UserController: ControllerBase
{
    private readonly AppDbContext _context;

    public UserController(AppDbContext context)
    {
        _context = context;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<User>>> GetUsers()
    {
        return await _context.User.ToListAsync();
    }

    [HttpGet]
    public ActionResult<List<object>> GetLikedItems(string SessionId, string Type)
    {
        var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
        var session = _context.UserSession.FirstOrDefault(l => l.Id == sessionIdGuid);

        if (session == null) {
            return NoContent();
        }

        var userVotes = _context.UserVote.Where(v => v.FK_User == session.FK_User && v.Type == Type && v.Vote);
        var elementIds = userVotes.Select(obj => obj.FK_Record).ToList();

        switch(Type){
            case "Product":
                return _context.Product.Where(obj => elementIds.Contains(obj.Id)).Select(obj => obj as object).ToList();
            case "Path":
                return _context.Path.Where(obj => elementIds.Contains(obj.Id)).Select(obj => obj as object).ToList();
            default:
                return NoContent();
        }
    }

    [HttpGet]
    public ActionResult<List<object>> GetBookmarkedItems(string SessionId, string Type)
    {
        var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
        var session = _context.UserSession.FirstOrDefault(l => l.Id == sessionIdGuid);

        if (session == null) {
            return NoContent();
        }

        var userBookmarks = _context.UserBookmark.Where(v => v.FK_User == session.FK_User && v.Type == Type);
        var elementIds = userBookmarks.Select(obj => obj.FK_Record).ToList();

        switch(Type){
            case "Product":
                return _context.Product.Where(obj => elementIds.Contains(obj.Id)).Select(obj => obj as object).ToList();
            default:
                return NoContent();
        }
    }

    [HttpPost]
    public ActionResult<Guid> CreateUser(string Name, string UserName, string Password)
    {
        var login = _context.UserLogin.FirstOrDefault(l =>  l.UserName == UserName);

        if (login != null) {
            return NoContent();
        }

        var newUser = new User() {
            Link = Guid.NewGuid(),
            Name = Name
        };
        _context.User.Add(newUser);
        _context.SaveChanges();

        var newLogin = new UserLogin() {
            FK_User = newUser.Id,
            UserName = UserName,
            HashedPassword = PasswordHasher.HashPassword(Password)
        };
        _context.UserLogin.Add(newLogin);
        _context.SaveChanges();
        
        var newSession = new UserSession() {
            FK_User = newUser.Id,
            ValidUntil = DateTime.UtcNow.AddDays(1)
        };
        _context.UserSession.Add(newSession);
        _context.SaveChanges();

        return newSession.Id;
    }

    [HttpPost]
    public ActionResult<Guid> Login(string UserName, string Password)
    {
        var login = _context.UserLogin.FirstOrDefault(l =>  l.UserName == UserName);

        if (login == null) {
            return NoContent();
        }

        if (!PasswordHasher.VerifyPassword(Password, login.HashedPassword)) {
            return NoContent();
        }

        var newSession = new UserSession() {
            FK_User = login.FK_User,
            ValidUntil = DateTime.UtcNow.AddDays(1)
        };
        _context.UserSession.Add(newSession);
        _context.SaveChanges();

        return newSession.Id;
    }

    [HttpPost]
    public ActionResult<bool> Logoff(string SessionId)
    {
        var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
        var session = _context.UserSession.FirstOrDefault(l =>  l.Id == sessionIdGuid);

        if(session != null) {
            session.ValidUntil = DateTime.UtcNow;
        }

        return true;
    }

    [HttpPost]
    public ActionResult<decimal> Vote(string SessionId, string Type, int Id, bool Vote)
    {
        int? FK_Parent = null;
        switch(Type){
            case "Product":
                var product = _context.Product.Find(Id);
                if (product == null) {
                    return NoContent();
                }
                FK_Parent = product.FK_Place;
            break;
            case "Path":
                var path = _context.Path.Find(Id);
                if (path == null) {
                    return NoContent();
                }
            break;
        }

        var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
        var session = _context.UserSession.FirstOrDefault(l => l.Id == sessionIdGuid);

        if (session == null) {
            return NoContent();
        }

        var userVote = _context.UserVote.FirstOrDefault(v => v.FK_User == session.FK_User && v.FK_Record == Id && v.Type == Type);
        
        if (userVote == null) {
            var newVote = new UserVote() {
                FK_User = session.FK_User,
                Type = Type,
                FK_Parent = FK_Parent,
                FK_Record = Id,
                Vote = Vote
            };
            _context.UserVote.Add(newVote);
            _context.SaveChanges();
        }

        decimal newRating = 0;
        if (userVote == null || userVote.Vote != Vote) {
            var ratingVariation = Vote ? 1 : -1;
            switch(Type){
                case "Product":
                    var product = _context.Product.Find(Id);
                    if (product != null) {
                        product.Rating += ratingVariation;
                        newRating = product.Rating;
                    }
                break;
                case "Path":
                    var path = _context.Path.Find(Id);
                    if (path != null) {
                        path.Rating += ratingVariation;
                        newRating = path.Rating;
                    }
                break;
            }
        }

        if (userVote != null) {
            userVote.Vote = Vote;
        }

        _context.SaveChanges();

        return newRating;
    }

    [HttpPost]
    public ActionResult<bool> SaveBookmark(string SessionId, string Type, int Id, bool Save)
    {
        int? FK_Parent = null;
        switch(Type){
            case "Product":
                var product = _context.Product.Find(Id);
                if (product == null) {
                    return NoContent();
                }
                FK_Parent = product.FK_Place;
            break;
        }

        var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
        var session = _context.UserSession.FirstOrDefault(l => l.Id == sessionIdGuid);

        if (session == null) {
            return NoContent();
        }

        var userVote = _context.UserBookmark.FirstOrDefault(v => v.FK_User == session.FK_User && v.FK_Record == Id && v.Type == Type);
        
        if (Save) {
            if (userVote == null) {
                var newVote = new UserBookmark() {
                    FK_User = session.FK_User,
                    Type = Type,
                    FK_Parent = FK_Parent,
                    FK_Record = Id
                };
                _context.UserBookmark.Add(newVote);
            }
        } else if (userVote != null) {
            _context.UserBookmark.Remove(userVote);
        }

        _context.SaveChanges();

        return Save;
    }
}