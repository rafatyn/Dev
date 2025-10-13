using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using CRTApp.Data;
using CRTApp.Models;
using CRTApp.Models.Request;
using System.Text.Json.Serialization;
using System.Text.Json;


[Route("[controller]/[action]")]
[ApiController]
public class ProductController: ControllerBase
{
    private readonly AppDbContext _context;

    public ProductController(AppDbContext context)
    {
        _context = context;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<Product>>> GetProducts()
    {
        return await _context.Product.ToListAsync();
    }

    [HttpPost]
    public async Task<ActionResult<List<Product>>> CreateProduct(List<CreateProductRequest> request)
    {
        List<Product> newProducts = new();

        foreach(CreateProductRequest item in request)
        {
            if(_context.Place.Find(item.PlaceId) == null){
                return NoContent();
            }

            newProducts.Add(new Product() {
                Link = Guid.NewGuid(),
                FK_Place = item.PlaceId,
                Name = item.Name,
                Description = item.Description,
                Price = item.Price,
                Order = item.Order,
                Rating = 0
            });
        }
        
        _context.Product.AddRange(newProducts);
        await _context.SaveChangesAsync();

        List<int> productsIds = newProducts.Select(obj => obj.Id).ToList();

        return await _context.Product.Where(obj => productsIds.Contains(obj.Id)).ToListAsync();
    }
}