const APIServer = "http://192.168.1.135:5291/";

export async function getJsonFromUrl(url: string) {
    return JSON.parse(await getTextFromUrl(url));
}

export async function getTextFromUrl(url: string, method?: string) {
    try {
        const response = await fetch(APIServer + url, {
            method: method != undefined ? method : 'GET'
        });
        var text = await response.text();
        if (text != undefined && text.length > 0 && response.ok) {
            return text;
        } else {
            return "";
        }
    } catch (error) {
        console.error('Error fetching data:', error);
        return "";
    }
}

// Find icons
// https://icons.expo.fyi/Index

// Find place Id
// https://developers.google.com/maps/documentation/places/web-service/place-id?hl=es-419#find-id

// Open place maps
// https://www.google.com/maps/search/?api=1&query=-3.695601%2C40.507237&query_place_id=ChIJAQAQ8c4rQg0RTU8LzWIGNKQ

// Open route in maps
// https://www.google.com/maps/dir/?api=1&destination=40.507168%2C-3.6957259&destination_place_id=ChIJAQAQ8c4rQg0RTU8LzWIGNKQ&travelmode=walking
// https://www.google.com/maps/dir/?api=1&destination=40.507168%2C-3.6957259&destination_place_id=ChIJAQAQ8c4rQg0RTU8LzWIGNKQ&travelmode=walking&waypoints=40.417607%2C-3.734099%7C40.432904%2C-3.605773&waypoint_place_ids=ChIJI7MQNxwpQg0RuSFEgNQ2g8s%7CChIJGcyLtUcvQg0RlOpS61LFROM

const MapsAPIKey = "?key=AIzaSyCPK6nK2bH23lWtp-c7iojNXHk2kaRsD3Y";
const PlaceAPIUrl = "https://places.googleapis.com/v1/places/";
const PlaceFields = "&fields=rating,userRatingCount,priceRange,currentOpeningHours,primaryTypeDisplayName";
const RouteAPIUrl = "https://www.google.com/maps/dir/?api=1travelmode=walking";

export async function getPlaceDetailsFromMaps(placeId: string) {
    try {
        const response = await fetch(PlaceAPIUrl + placeId + MapsAPIKey + PlaceFields);
        var json = await response.text();
        if (json != undefined && json.length > 0) {
            return JSON.parse(json);
        } else {
            return "";
        }
    } catch (error) {
        console.error('Error fetching data:', error);
        return "";
    }
}