using System;

namespace CRTApp.Models.Request
{
    public class CreateProductRequest
    {
        public required string Name { get; set; }
        public required string Description { get; set; }
        public required float Price { get; set; }
        public required int PlaceId { get; set; }
        public required int Order { get; set; }
    }
}