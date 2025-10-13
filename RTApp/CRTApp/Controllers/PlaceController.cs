using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using CRTApp.Data;
using CRTApp.Models;
using CRTApp.Models.Request;
using System.Text.Json.Serialization;
using System.Text.Json;


[Route("[controller]/[action]")]
[ApiController]
public class PlaceController: ControllerBase
{
    private readonly AppDbContext _context;

    public PlaceController(AppDbContext context)
    {
        _context = context;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<Place>>> GetPlaces()
    {
        return await _context.Place.ToListAsync();
    }

    [HttpPost]
    public async Task<ActionResult<IEnumerable<Place>>> CreatePlace([FromBody] List<CreatePlaceRequest> request)
    {
        List<Place> newPlaces = new();

        foreach(CreatePlaceRequest item in request)
        {
            newPlaces.Add(new Place() {
                Link = Guid.NewGuid(),
                Name = item.Name,
                Longitude = item.Longitude,
                Latitude = item.Latitude,
                GoogleId = item.GoogleId
            });
        }

        _context.Place.AddRange(newPlaces);
        await _context.SaveChangesAsync();

        List<int> placeIds = newPlaces.Select(obj => obj.Id).ToList();

        return await _context.Place.Where(obj => placeIds.Contains(obj.Id)).ToListAsync();
    }

    [HttpGet]
    public ActionResult<IEnumerable<Product>> GetPlaceProducts(int PlaceId, string SessionId = "")
    {
        if (_context.Place.Find(PlaceId) == null) {
            return NoContent();
        }
        
        var products = _context.Product.Where(obj => obj.FK_Place == PlaceId).ToList();

        if (!string.IsNullOrEmpty(SessionId)) {
            var sessionIdGuid = Guid.Parse(SessionId.Replace("\"", ""));
            var session = _context.UserSession.Find(sessionIdGuid);

            if (session != null) {
                var userVotes = _context.UserVote.Where(obj => obj.FK_User == session.FK_User && obj.FK_Parent == PlaceId && obj.Type == "Product").ToList();
                var userBookmarks = _context.UserBookmark.Where(obj => obj.FK_User == session.FK_User && obj.FK_Parent == PlaceId && obj.Type == "Product").ToList();

                foreach(var product in products) {
                    if (userVotes.Any()) {
                        var vote = userVotes.FirstOrDefault(obj => obj.FK_Record == product.Id);
                        product.Liked = vote != null ? vote.Vote : false;
                    }
                    if (userBookmarks.Any()) {
                        var bookmark = userBookmarks.FirstOrDefault(obj => obj.FK_Record == product.Id);
                        product.Bookmarked = bookmark != null ? true : false;
                    }
                }
            }
        }

        foreach(var product in products) {
            var imageFilePath = $"./Img/Product/{product.Id}.webp";
            if (System.IO.File.Exists(imageFilePath)) {
                var fileBytes = System.IO.File.ReadAllBytes(imageFilePath);
                product.Image = Convert.ToBase64String(fileBytes);
            }
        }

        return products;
    }
}