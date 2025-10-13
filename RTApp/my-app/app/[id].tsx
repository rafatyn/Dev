import { Text, View, StyleSheet, FlatList, ActivityIndicator, Platform, Pressable, Image, TouchableOpacity, Button } from 'react-native';
import { Link, Stack, useLocalSearchParams } from 'expo-router';
import { useState, useEffect, useRef } from 'react';

import { getJsonFromUrl, getPlaceDetailsFromMaps } from "@/components/fetch";
import { IMapsPlace, IPlace } from '@/components/types';

import FontAwesome from '@expo/vector-icons/FontAwesome';
import MaterialIcons from '@expo/vector-icons/MaterialIcons';

import MapView, { Marker, LatLng } from 'react-native-maps';

import * as Linking from 'expo-linking';
import * as Location from 'expo-location';
import Screen from '@/app/Screen';

export default function Path() {

    const enableLocation = true;

    const { id, name } = useLocalSearchParams<{ id: string, name: string }>();
    const [places, setPlaces] = useState(Array<IPlace>);
    var map = useRef<MapView | null>(null);
    const [details, setDetails] = useState<Map<number, IMapsPlace>>();
    const [locationEnabled, setLocationEnabled] = useState(false);

    const url = 'Path/GetPathPlaces?PathId=' + id;
    const RouteAPIUrl = "https://www.google.com/maps/dir/?api=1";
    
    useEffect(() => {
        if(enableLocation) {
            Location.getForegroundPermissionsAsync().then(permission => {
                if (!permission.granted) {
                    Location.requestForegroundPermissionsAsync().then(permissionRequest => {
                        if (permissionRequest.granted) {
                            Location.hasServicesEnabledAsync().then(value => {
                                if (!value){
                                    Location.getCurrentPositionAsync().then(position => {
                                        if (position != null) {
                                            setLocationEnabled(true);
                                        }
                                    });
                                } else {
                                    setLocationEnabled(true);
                                }
                            });
                        } else {
                            setLocationEnabled(true);
                        }
                    });
                } else {
                    Location.hasServicesEnabledAsync().then(value => {
                        if (!value){
                            Location.getCurrentPositionAsync().then(position => {
                                if (position != null) {
                                    setLocationEnabled(true);
                                }
                            });
                        } else {
                            setLocationEnabled(true);
                        }
                    });
                }
            });
        }
        getJsonFromUrl(url).then(itemList => {
            setPlaces(itemList);
            itemList.forEach(function (place: IPlace) {
                getPlaceDetailsFromMaps(place.googleId).then(detail => {
                    setDetails((prevMap) => new Map(prevMap).set(place.id, 
                        { 
                            rating: detail.rating, 
                            ratingCount: detail.userRatingCount,
                            openNow: detail.currentOpeningHours.openNow, 
                            nextDateChange: new Date(detail.currentOpeningHours.openNow ? Date.parse(detail.currentOpeningHours.nextCloseTime) : Date.parse(detail.currentOpeningHours.nextOpenTime)),
                            startPrice: detail.priceRange.startPrice.units,
                            endPrice: detail.priceRange.endPrice.units,
                            currency: detail.priceRange.startPrice.currencyCode == "EUR" ? "€" : "$",
                            placeType: detail.primaryTypeDisplayName.text
                        }));
                });
            });
        });
    }, []);

    function startRoute() {
        var waypoints = Array<string>();
        var waypointsIds = Array<string>();
        var destination = "";
        var destinationId = "";
        places.forEach(function (place: IPlace, index: number) {
            if (index == places.length - 1) {
                destination = place.name.split(" ").join("%2C");
                destinationId = place.googleId;
            } else {
                waypoints.push(place.name.split(" ").join("%2C"));
                waypointsIds.push(place.googleId);
            }
        });
        Linking.openURL(RouteAPIUrl + "&destination=" + destination + "&destination_place_id=" + destinationId + (waypoints.length > 0 ? "&waypoints=" + waypoints.join("%7C") + "&waypoint_place_ids=" + waypointsIds.join("%7C") : "") + "&travelmode=walking");
    }

    return (
        <Screen>
            <Stack.Screen
                options={{
                    headerTitle: name,
                    headerTitleAlign: "center",
                    headerLeft: undefined
                }}
            />
            { places != undefined && places.length > 0 ? 
            (
                <View style={{ flex: 1 }}>
                    <View style={{ height: "35%", margin: -20 }}>
                        <MapView                             
                            ref={ref => {
                                map.current = ref;
                            }}
                            style={styles.flexContainer}
                            showsUserLocation
                            onMapReady={() => { 
                                let coordinates: LatLng[] = [];
                                places.forEach((marker) => {
                                    coordinates.push({ latitude: marker.latitude, longitude: marker.longitude });
                                });
                                map.current?.fitToCoordinates(coordinates, { edgePadding: {top: 40, right: 40, bottom: 40, left: 40}, animated: true });
                            }}>
                            {places.map((place, index) => (
                                <Marker
                                    key={index}
                                    coordinate={{
                                        latitude: place.latitude,
                                        longitude: place.longitude
                                    }}
                                    title={place.name}
                                    description={place.link}
                                />
                            ))}
                        </MapView>
                    </View>
                    <View style={{ display: "flex", flexDirection: "row", justifyContent: "space-between", alignContent: "center", backgroundColor: "#1f2937", marginTop: 20, marginLeft: -20, marginRight: -20, padding: 10, paddingLeft: 20, paddingRight: 20 }}>
                        <View>
                            <Text style={{ color: "#BFBFBF", fontSize: 12 }}>Restaurants</Text>
                            <Text style={{ color: "white", fontWeight: "bold", fontSize: 18 }}>{ places.length }</Text>
                        </View>
                        <View>
                            <Text style={{ color: "#BFBFBF", fontSize: 12 }}>Places within</Text>
                            <Text style={{ color: "white", fontWeight: "bold", fontSize: 18 }}>300 m</Text>
                        </View>
                        <View style={{ paddingTop: 3, borderRadius: 20 }}>
                            <Button title='Start' onPress={startRoute} disabled={!locationEnabled}/>
                        </View>                        
                    </View>
                    <FlatList 
                        className='h-1/6 mb-4'
                        data={places.sort((a, b) => {
                            if (a.order > b.order) {
                                return 1;
                            } else if (a.order < b.order) {
                                return -1;
                            } else {
                                return 0;
                            }
                        })}
                        keyExtractor={(item) => item.link }
                        renderItem={({ item }) => (
                            <View>
                                <Link href={{ pathname: '/place/[id]', params: { id: item.id, name: item.name } }} asChild>
                                    <TouchableOpacity>
                                        <View style={{ height: 100, backgroundColor: "#1f2937", padding: 20, marginTop: 15, borderRadius: 20, justifyContent: 'center' }}>
                                            { details != undefined && details.has(item.id) ? 
                                            (
                                                <View style={{ flex: 1, flexDirection: "row", justifyContent: "space-between", alignItems: "center" }}>
                                                    <View style={{ flex: 1, flexDirection: "row", justifyContent: "space-between", alignItems: "center" }}>
                                                        <View>
                                                            <Text style={{ color: "white", fontWeight: "bold", fontSize: 20 }}>{item.name}</Text>
                                                            <Text style={{ color: "#BFBFBF", fontSize: 14 }}>{details.get(item.id)?.placeType} {'\u2022'}
                                                                {" "}{details.get(item.id)?.startPrice} - {details.get(item.id)?.endPrice} {details.get(item.id)?.currency}</Text>
                                                            <View style={{ marginTop: 5 }}>
                                                                {details.get(item.id)?.openNow ?
                                                                (
                                                                    <Text style={{ color: "#4CAF50" }}>Open until {details.get(item.id)?.nextDateChange.toLocaleTimeString('es-ES', { hour: 'numeric', minute: 'numeric', second: undefined })}</Text>
                                                                )
                                                                : 
                                                                (
                                                                    <View style={{ display: "flex", flexDirection: "row" }}>
                                                                        <Text style={{ color: "#F44336" }}>Closed</Text><Text style={{ color: "white" }}>, opens at {details.get(item.id)?.nextDateChange.toLocaleTimeString('es-ES', { hour: 'numeric', minute: 'numeric', second: undefined })}</Text>
                                                                    </View>
                                                                )}
                                                            </View>                                                            
                                                        </View>
                                                        <View>
                                                            <View style={{ display: "flex", flexDirection: "row", alignItems: "center" }}>
                                                                <FontAwesome name="star" size={20} color="#FFFF00" />
                                                                <Text style={{ color: "white", marginLeft: 5 }}>{details.get(item.id)?.rating}</Text>
                                                            </View>
                                                            <Text style={{ color: "white", textAlign: "center" }}>({details.get(item.id)?.ratingCount})</Text>
                                                        </View>
                                                    </View>
                                                    <View style={{ marginLeft: 5, width: 17 }}>
                                                        <MaterialIcons name="keyboard-arrow-right" size={24} color="#3b82f6" />
                                                    </View>
                                                </View>
                                            )
                                            :
                                            (
                                                <View>
                                                    <Text style={styles.text}>{item.name}</Text>
                                                </View>
                                            )}
                                        </View>
                                    </TouchableOpacity>
                                </Link>
                            </View>
                        )}
                    />
                </View>
            )
            : 
            (
                <View style={[styles.flexContainer,styles.verticalCenter,styles.horizontalCenter]}>
                    <Text style={styles.text}>Loading...</Text>
                    <ActivityIndicator/>
                </View>
            )}
        </Screen>
    );
}

const styles = StyleSheet.create({
    flexContainer: {
        flex: 1,
    },
    flexRow: {
        flexDirection: 'row'
    },
    verticalCenter: {
        justifyContent: 'center',
    },
    horizontalCenter: {
        alignItems: 'center',
    },
    text: {
        color: '#fff',
    },
});
