import { Text, View, StyleSheet, FlatList, ActivityIndicator, Pressable, Button, TouchableOpacity, Image, Modal, ScrollView } from 'react-native';
import { Link, useFocusEffect } from 'expo-router';
import * as SecureStore from 'expo-secure-store';
import { useState, useCallback } from 'react';

import { getJsonFromUrl, getTextFromUrl } from "@/components/fetch";
import { IPath } from '@/components/types';
import Screen from '@/app/Screen';
import FontAwesome from '@expo/vector-icons/FontAwesome';
import FontAwesome6 from '@expo/vector-icons/FontAwesome6';
import MaterialIcons from '@expo/vector-icons/MaterialIcons';

export default function Index() {
    const [paths, setPaths] = useState(Array<IPath>);
    const [showLogin, setShowLogin] = useState<boolean>(false);
    const [refresh, setRefresh] = useState<boolean>(false);

    const [filterPopular, setFilterPopular] = useState<boolean>(false);
    const [filterNearMe, setFilterNearMe] = useState<boolean>(false);
    const [filterCity, setFilterCity] = useState<string>("");
    const [filterPrice, setFilterPrice] = useState<number>(0);
    const [filterLiked, setFilterLiked] = useState<boolean>(false);

    const url = 'Path/GetPaths';
    const voteUrl = 'User/Vote?Type=Path&Id=';

    useFocusEffect(
        useCallback(() => {
            var sessionId = SecureStore.getItem('sessionId');
            getJsonFromUrl(url + (sessionId != null ? "?SessionId=" + sessionId : "")).then(itemList => {
                setPaths(itemList);
            });
        }, [])
    );
    
    function vote(itemId: number) {
        var sessionId = SecureStore.getItem('sessionId');
        if(sessionId == undefined) {
            setShowLogin(true);
        } else {
            var actualPath = paths.find((value) => value.id == itemId);
            if (actualPath != null) {
                getTextFromUrl(voteUrl + itemId + "&Vote=" + !actualPath.liked + "&SessionId=" + sessionId, "POST").then(rating => {
                    actualPath.rating = Number.parseFloat(rating);
                    actualPath.liked = !actualPath.liked;
                    setRefresh(!refresh);
                });
            }
        }
    }

    return (
        <Screen>
            <View>
                <ScrollView horizontal contentContainerStyle={{ marginBottom: 15, columnGap: 15, height: 30 }}>
                    <View style={{ backgroundColor: (filterPopular ? "#3b82f6" : "#1f2937"), borderRadius: 20, padding: 3, paddingLeft: 10, paddingRight: 10 }}>
                        <TouchableOpacity onPress={() => { setFilterPopular(!filterPopular) }}>
                            <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>Popular</Text>
                        </TouchableOpacity>
                    </View>
                    <View style={{ backgroundColor: (filterNearMe ? "#3b82f6" : "#1f2937"), borderRadius: 20, padding: 3, paddingLeft: 10, paddingRight: 10 }}>
                        <TouchableOpacity onPress={() => { setFilterNearMe(!filterNearMe) }}>
                            <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>Near me</Text>
                        </TouchableOpacity>
                    </View>
                    <View style={{ backgroundColor: (filterCity ? "#3b82f6" : "#1f2937"), borderRadius: 20, padding: 3, paddingLeft: 10, paddingRight: 10 }}>
                        <TouchableOpacity onPress={() => { setFilterCity("") }}>
                            <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>City</Text>
                        </TouchableOpacity>
                    </View>
                    <View style={{ backgroundColor: (filterPrice ? "#3b82f6" : "#1f2937"), borderRadius: 20, padding: 3, paddingLeft: 10, paddingRight: 10 }}>
                        <TouchableOpacity onPress={() => { setFilterPrice(0) }}>
                            <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>Price</Text>
                        </TouchableOpacity>
                    </View>
                    <View style={{ backgroundColor: (filterLiked ? "#3b82f6" : "#1f2937"), borderRadius: 20, padding: 3, paddingLeft: 10, paddingRight: 10 }}>
                        <TouchableOpacity onPress={() => { setFilterLiked(!filterLiked) }}>
                            <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>Liked</Text>
                        </TouchableOpacity>
                    </View>
                </ScrollView>
            </View>
            <View style={{ flex: 1 }}>
                { paths != undefined && paths.length > 0 ? 
                (
                    <View style={{ flex: 1 }}>
                        <FlatList
                            data={paths.filter((obj) => {
                                var valid = true;
                                if (filterPopular && obj.rating < 1) {
                                    valid = false;
                                }
                                if (filterLiked && !obj.liked) {
                                    valid = false;
                                }
                                return valid;
                            }).sort((a, b) => {
                                if (a.rating < b.rating) {
                                    return 1;
                                } else if (a.rating > b.rating) {
                                    return -1;
                                } else {
                                    if (a.name > b.name) {
                                        return 1;
                                    } else if (a.name < b.name) {
                                        return -1;
                                    } else {
                                        return 0;
                                    }
                                }
                            })}
                            extraData={refresh}
                            keyExtractor={(item) => item.link }
                            renderItem={({ item }) => (
                                <View>
                                    <Link href={{ pathname: '/[id]', params: { id: item.id, name: item.name } }} asChild>
                                        <TouchableOpacity>
                                            <View style={{ flex: 1, flexDirection: "column", backgroundColor: "#1f2937", borderRadius: 20, marginBottom: 20 }}>
                                                <Image style={{ width: "100%", height: 150, borderTopLeftRadius: 20, borderTopRightRadius: 20 }} source={{uri: 'data:image/png;base64,' + item.image }}/>
                                                <View style={{ position: "absolute", top: 10, left: 10, backgroundColor: "#1f2937", borderRadius: 20, padding: 5, paddingLeft: 10, paddingRight: 10 }}>
                                                    <Text style={{ color: "white" }}>{item.location}</Text>
                                                </View>
                                                <View style={{ flex: 1, flexDirection: "column", backgroundColor: "#1f2937", borderBottomLeftRadius: 20, borderBottomRightRadius: 20, padding: 15 }}>
                                                    <View style={{ flex: 1, flexDirection: "row", justifyContent: 'space-between', alignItems: "center" }}>
                                                        <View>
                                                            <Text style={{ color: "white", fontWeight: "bold", fontSize: 20 }}>{item.name}</Text>
                                                            <Text style={{ color: "#BFBFBF", fontSize: 14 }}>Estimated price ~{item.estimatedPrice} {item.currency}</Text>
                                                        </View>
                                                        <View style={{ marginLeft: 5, width: 17 }}>
                                                            <MaterialIcons name="keyboard-arrow-right" size={24} color="#3b82f6" />
                                                        </View>
                                                    </View>
                                                    <View style={{ flex: 1, flexDirection: "row", justifyContent: 'space-between', alignItems: "center", marginTop: 10 }}>
                                                        <View style={{ display: "flex", flexDirection: "row", alignItems: "center", backgroundColor: "#374151", borderRadius: 20, padding: 5, paddingLeft: 10, paddingRight: 10 }}>
                                                            <View>
                                                                <TouchableOpacity onPress={() => { vote(item.id) }}>
                                                                    <FontAwesome name={(item.liked ? "heart" : "heart-o" )} size={20} color="red" />
                                                                </TouchableOpacity>
                                                            </View>
                                                            <Text style={{ color: "white", marginLeft: 5 }}>{item.rating}</Text>
                                                        </View>
                                                        { item.rating > 0 && (
                                                            <View style={{ display: "flex", flexDirection: "row" }}>
                                                                <FontAwesome6 name="fire-flame-curved" size={16} color="orange" />
                                                                <Text style={{ color: "white", fontWeight: "bold", marginLeft: 5 }}>Popular</Text>
                                                            </View>
                                                        )}
                                                    </View>
                                                </View>
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
            </View>
            <Modal animationType="fade" transparent={true} visible={showLogin} onRequestClose={() => { setShowLogin(false); }}>
                <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center', backgroundColor: 'rgba(0,0,0,0.4)' }}>
                    <View style={{ backgroundColor: 'white', height: 100, width: 200, borderRadius: 10, alignItems: 'center', justifyContent: 'center' }}>
                        <Text style={{ color: 'black' }}>You need to sign in to vote</Text>
                        <Link href="/login" style={{ marginTop: 10 }} asChild>
                            <TouchableOpacity onPress={() => { setShowLogin(false) }}>
                                <Text style={{ backgroundColor: "#2196F3", padding: 5, borderRadius: 2, textTransform: "uppercase", color: "white", textAlign: "center" }}>Sign In</Text>
                            </TouchableOpacity>
                        </Link>
                    </View>
                </View>
            </Modal>
        </Screen>
    );
}

const styles = StyleSheet.create({
    flexContainer: {
        flex: 1,
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
    pathItem: {
        height: 50,
        paddingLeft: 20,
        marginBottom: 10,
        borderWidth: 1,
        borderColor: 'white',
        borderRadius: 10,        
        justifyContent: 'center',
    },
});
