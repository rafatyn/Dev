export interface IPath {
    id: number,
    link: string,
    name: string,
    location: string,
    estimatedPrice: number,
    currency: string,
    rating: number,
    liked: boolean,
    image: string
}

export interface IPlace {
    id: number,
    link: string,
    name: string,
    longitude: number,
    latitude: number,
    googleId: string,
    order: number
}

export interface IMapsPlace {
    placeType: string,
    rating: number,
    ratingCount: number,
    openNow: boolean,
    nextDateChange: Date,
    startPrice: number,
    endPrice: number,
    currency: string,
}

export interface IProduct {
    id: number,
    link: string,
    name: string,
    description: string,
    price: number,
    order: number,
    rating: number,
    liked: boolean,
    bookmarked: boolean,
    image: string
}