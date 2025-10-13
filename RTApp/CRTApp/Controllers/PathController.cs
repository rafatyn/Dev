using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using CRTApp.Data;
using CRTApp.Models;
using Path = CRTApp.Models.Path;
using CRTApp.Models.Request;

[Route("[controller]/[action]")]
[ApiController]
public class PathController: ControllerBase
{
    private readonly AppDbContext _context;

    public PathController(AppDbContext context)
    {
        _context = context;
    }

    [HttpGet]
    public ActionResult<IEnumerable<Path>> GetPaths(string SessionId = "")
    {
        var paths = _context.Path.ToList();

        if (!string.IsNullOrEmpty(SessionId)) {
            var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
            var session = _context.UserSession.Find(sessionIdGuid);

            if (session != null) {
                var userVotes = _context.UserVote.Where(obj => obj.FK_User == session.FK_User && obj.FK_Parent == null && obj.Type == "Path").ToList();

                foreach(var path in paths) {
                    if (userVotes.Any()) {
                        var vote = userVotes.FirstOrDefault(obj => obj.FK_Record == path.Id);
                        path.Liked = vote != null ? vote.Vote : false;
                    }
                }
            }
        }

        foreach(var path in paths) {
            var imageFilePath = $"./Img/Path/{path.Id}.webp";
            if (System.IO.File.Exists(imageFilePath)) {
                var fileBytes = System.IO.File.ReadAllBytes(imageFilePath);
                path.Image = Convert.ToBase64String(fileBytes);
            }
        }
        
        return paths;
    }

    [HttpPost]
    public async Task<ActionResult<Path>> CreatePath(string Name)
    {
        var newPath = new Path() {
            Link = Guid.NewGuid(),
            Name = Name
        };
        _context.Path.Add(newPath);
        await _context.SaveChangesAsync();

        return await _context.Path.FindAsync(newPath.Id);
    }

    [HttpGet]
    public ActionResult<IEnumerable<Place>> GetPathPlaces(int PathId)
    {
        if(_context.Path.Find(PathId) == null){
            return NoContent();
        }

        var currentPathPlaces = _context.PathPlace.Where(obj => obj.FK_Path == PathId).ToList();
        var currentPathPlaceIds = currentPathPlaces.Select(obj => obj.FK_Place).ToList();

        var places = _context.Place.Where(obj => currentPathPlaceIds.Contains(obj.Id)).ToList();

        foreach(var place in places) {
            var pathPlace = currentPathPlaces.FirstOrDefault(obj => obj.FK_Place ==  place.Id);
            place.Order = pathPlace.Order;
        }

        return places;
    }

    [HttpPost]
    public async Task<ActionResult<IEnumerable<Place>>> AddPlaceToPath([FromBody] List<AddPlaceToPathRequest> request)
    {

        List<PathPlace> newPathPlaces = new();

        foreach(AddPlaceToPathRequest item in request)
        {
            if(_context.Path.Find(item.PathId) == null)
                return NoContent();

            if(_context.Place.Find(item.PlaceId) == null)
                return NoContent();

            var currentPathPlace = _context.PathPlace.Where(obj => obj.FK_Path == item.PathId).ToList();
            foreach(var pathPlace in currentPathPlace.Where(obj => obj.Order >= item.Order).ToList())
                pathPlace.Order = pathPlace.Order + 1;

            newPathPlaces.Add(new PathPlace() {
                FK_Path = item.PathId,
                FK_Place = item.PlaceId,
                Order = item.Order
            });
        }

        _context.PathPlace.AddRange(newPathPlaces);
        await _context.SaveChangesAsync();

        List<int> currentPathPlaceIds = newPathPlaces.Select(obj => obj.FK_Place).Distinct().ToList();

        return await _context.Place.Where(obj => currentPathPlaceIds.Contains(obj.Id)).ToListAsync();
    }

    [HttpPost]
    public async Task<ActionResult<IEnumerable<Place>>> DeletePlaceIntoPath(int PathId, int PlaceId)
    {
        if(_context.Path.Find(PathId) == null){
            return NoContent();
        }

        if(_context.Place.Find(PlaceId) == null){
            return NoContent();
        }

        var pathPlace = _context.PathPlace.FirstOrDefault(obj => obj.FK_Path == PathId && obj.FK_Place == PlaceId);
        if(pathPlace == null){
            return NoContent();
        }

        var currentPathPlace = _context.PathPlace.Where(obj => obj.FK_Path == PathId).ToList();
        foreach(var otherPathPlace in currentPathPlace.Where(obj => obj.Order > pathPlace.Order).ToList()){
            otherPathPlace.Order = otherPathPlace.Order - 1;
        }

        _context.PathPlace.Remove(pathPlace);
        await _context.SaveChangesAsync();

        var currentPathPlaceIds = currentPathPlace.Select(obj => obj.FK_Place).ToList();
        currentPathPlaceIds.Remove(pathPlace.FK_Place);

        return await _context.Place.Where(obj => currentPathPlaceIds.Contains(obj.Id)).ToListAsync();
    }
}