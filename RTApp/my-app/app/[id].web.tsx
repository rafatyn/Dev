import { Text, View, StyleSheet, FlatList, ActivityIndicator, Platform, Pressable, Image } from 'react-native';
import { Link, Stack, useLocalSearchParams } from 'expo-router';
import { useState, useEffect, useRef } from 'react';

import { getJsonFromUrl, getPlaceDetailsFromMaps } from "@/components/fetch";
import { IPlace } from '@/components/types';

import FontAwesome from '@expo/vector-icons/FontAwesome';

import MapView, { LoadScript, Marker, MapViewHandle } from "@preflower/react-native-web-maps";

import * as Location from 'expo-location';
import Screen from '@/app/Screen';

export default function Path() {

    const enableLocation = false;

    const { id, name } = useLocalSearchParams<{ id: string, name: string }>();
    const [places, setPlaces] = useState(Array<IPlace>);
    const [details, setDetails] = useState<Map<number, [number, number, boolean, Date]>>();

    const url = 'Path/GetPathPlaces?PathId=' + id;
    
    useEffect(() => {
        if(enableLocation){
            Location.getForegroundPermissionsAsync().then(permission => {
                if (!permission.granted) {
                    Location.requestForegroundPermissionsAsync().then(permissionRequest => {
                        if (permissionRequest.granted) {
                            Location.hasServicesEnabledAsync().then(value => {
                                if (!value){
                                    Location.getCurrentPositionAsync();
                                }
                            });
                        }
                    });
                } else {
                    Location.hasServicesEnabledAsync().then(value => {
                        if (!value){
                            Location.getCurrentPositionAsync();
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
                        [ detail.rating, detail.userRatingCount, detail.currentOpeningHours.openNow, new Date(detail.currentOpeningHours.openNow ? Date.parse(detail.currentOpeningHours.nextCloseTime) : Date.parse(detail.currentOpeningHours.nextOpenTime)) ]));
                });
            });
        });
    }, []);

    const map = useRef<MapViewHandle | null>(null)
    const [googleMap, setGoogleMap] = useState<google.maps.Map>()

    return (
        <Screen>
            <Stack.Screen
                options={{
                    headerTitle: name,
                    headerTitleAlign: "center"
                }}
            />
            { places != undefined && places.length > 0 ? 
            (
                <View className='h-full'>
                    <FlatList 
                        className='h-1/6 mb-4'
                        data={places}
                        keyExtractor={(item) => item.link }
                        renderItem={({ item }) => (
                            <View>
                                <Link href={{ pathname: '/place/[id]', params: { id: item.id, name: item.name } }} asChild>
                                    <Pressable>
                                        <View style={styles.placeItem}>
                                            { details != undefined && details.has(item.id) ? 
                                            (
                                                <View className='flex flex-row justify-between'>
                                                    <View className='flex-grow'>
                                                        <Text style={styles.text}>{item.name}</Text>
                                                        <Text style={styles.text}><Text className={details.get(item.id)?.[2] ? 'color-green-500' : 'color-red-500'}>{details.get(item.id)?.[2] ? "Open" : "Closed"}</Text>
                                                            {details.get(item.id)?.[2] ? ", closes at: " : ", opens at: "}
                                                            {details.get(item.id)?.[3].toLocaleTimeString('es-ES', { hour: 'numeric', minute: 'numeric', second: undefined })}</Text>
                                                    </View>
                                                    <View>
                                                        <View style={styles.starContainer}>
                                                            {[0.5,1,1.5,2,2.5,3,3.5,4,4.5,5].map((value) => (
                                                                <FontAwesome key={item.id + "_" + value} style={[styles.starImage, value % 1 == 0 ? styles.rigthStarImage : ""]} 
                                                                    name="star-half" size={20} color={(details.get(item.id)?.[0] ?? 0) >= value ? "rgb(255, 255, 0)" : "rgb(100, 100, 100)"} />
                                                            ))}
                                                        </View>
                                                        <Text style={styles.text} className='self-end'>({details.get(item.id)?.[1]})</Text>
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
                                    </Pressable>
                                </Link>
                            </View>
                        )}
                    />
                    <View style={styles.flexContainer}>
                        <View style={styles.flexContainer}>
                            <LoadScript googleMapsApiKey="#">
                                <MapView
                                    ref={map}
                                    style={styles.flexContainer}
                                    initialRegion={{
                                        latitude: 52.5063615,
                                        longitude: 13.3362866,
                                        latitudeDelta: 0.2922,
                                        longitudeDelta: 0.2421
                                    }}
                                    onMapReady={() => { 
                                        const bounds = new window.google.maps.LatLngBounds();
                                        places.forEach((marker) => {
                                            bounds.extend(new window.google.maps.LatLng(marker.latitude, marker.longitude));
                                        });
                                        var newRegion = {
                                            latitude: bounds.getCenter().lat(),
                                            longitude: bounds.getCenter().lng(),
                                            latitudeDelta: 0.1,
                                            longitudeDelta: 0.1
                                        };
                                        map.current?.animateToRegion(newRegion);
                                    }}>
                                    {places.map((place) => (
                                        <Marker
                                            coordinate={{
                                                latitude: place.latitude,
                                                longitude: place.longitude
                                            }}
                                            scaledSize={{
                                                width: 40,
                                                height: 41
                                            }}
                                        />
                                    ))}
                                </MapView>
                            </LoadScript>
                        </View>
                    </View>
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
    placeItem: {
        height: 100,
        paddingLeft: 20,
        paddingRight: 20,
        marginBottom: 10,
        borderWidth: 1,
        borderColor: 'white',
        borderRadius: 10,        
        justifyContent: 'center'        
    },
    starContainer: {
        flex: 1,
        flexDirection: 'row',
        rowGap: 0
    },
    starImage: {
        margin: 0,
        height: 20,
        width: 9,
        resizeMode: 'contain',
        tintColor: 'rgb(100, 100, 100)'
    },
    rigthStarImage: {
        marginRight: 1,
        transform: [{
            rotateY: '180deg'
        }]
    },
    fillStarImage: {
        tintColor:'rgb(255, 255, 0)'
    }
});
