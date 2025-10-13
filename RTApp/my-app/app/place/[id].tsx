import { Text, View, StyleSheet, FlatList, ActivityIndicator, Image, TouchableOpacity, Modal, Button } from 'react-native';
import { Link, router, Stack, useFocusEffect, useLocalSearchParams } from 'expo-router';
import * as SecureStore from 'expo-secure-store';
import { useState, useEffect, useCallback } from 'react';

import { getJsonFromUrl, getTextFromUrl } from "@/components/fetch";
import { IProduct } from '@/components/types';
import Screen from '@/app/Screen';

import FontAwesome from '@expo/vector-icons/FontAwesome';
import FontAwesome6 from '@expo/vector-icons/FontAwesome6';

export default function Path() {
    const { id, name } = useLocalSearchParams<{ id: string, name: string }>();
    const [products, setProducts] = useState(Array<IProduct>);
    const [showLogin, setShowLogin] = useState<boolean>(false);
    const [refresh, setRefresh] = useState<boolean>(false);

    const url = 'Place/GetPlaceProducts?PlaceId=' + id;
    const voteUrl = 'User/Vote?Type=Product&Id=';
    const bookmarkUrl = 'User/SaveBookmark?Type=Product&Id=';

    useFocusEffect(
        useCallback(() => {
            var sessionId = SecureStore.getItem('sessionId');
            getJsonFromUrl(url + (sessionId != null ? "&SessionId=" + sessionId : "")).then(itemList => {
                setProducts(itemList);
            });
        }, [])
    );

    function vote(itemId: number) {
        var sessionId = SecureStore.getItem('sessionId');
        if(sessionId == null) {
            setShowLogin(true);
        } else {
            var actualProduct = products.find((value) => value.id == itemId);
            if (actualProduct != null) {
                getTextFromUrl(voteUrl + itemId + "&Vote=" + !actualProduct.liked + "&SessionId=" + sessionId, "POST").then(rating => {
                    actualProduct.rating = Number.parseFloat(rating);
                    actualProduct.liked = !actualProduct.liked;
                    setRefresh(!refresh);
                });
            }
        }
    }

    function bookmark(itemId: number) {
        var sessionId = SecureStore.getItem('sessionId');
        if(sessionId == null) {
            setShowLogin(true);
        } else {
            var actualProduct = products.find((value) => value.id == itemId);
            if (actualProduct != null) {
                getTextFromUrl(bookmarkUrl + itemId + "&Save=" + !actualProduct.bookmarked + "&SessionId=" + sessionId, "POST").then(rating => {
                    actualProduct.bookmarked = !actualProduct.bookmarked;
                    setRefresh(!refresh);
                });
            }
        }
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
            { products != undefined && products.length > 0 ? 
            (
                <View style={styles.flexContainer}>
                    <FlatList 
                        style={{ flexGrow: 0 }}
                        data={products.sort((a, b) => {
                            if (a.order > b.order) {
                                return 1;
                            } else if (a.order < b.order) {
                                return -1;
                            } else {
                                return 0;
                            }
                        })}
                        extraData={refresh}
                        keyExtractor={(item) => item.link }
                        renderItem={({ item }) => (
                            <View style={{ flex: 1, flexDirection: "column", backgroundColor: "#1f2937", borderRadius: 20, marginBottom: 20 }}>
                                <Image style={{ width: "100%", height: 150, borderTopLeftRadius: 20, borderTopRightRadius: 20 }} source={{uri: 'data:image/png;base64,' + item.image }}/>
                                <View style={{ position: "absolute", top: 10, right: 10, backgroundColor: "#1f2937", borderRadius: 20, padding: 5, paddingLeft: 10, paddingRight: 10 }}>
                                    <TouchableOpacity onPress={() => { bookmark(item.id) }}>
                                        <FontAwesome name={(item.bookmarked ? "bookmark" : "bookmark-o" )} size={20} color="#3b82f6" />
                                    </TouchableOpacity>
                                </View>
                                <View style={{ flex: 1, flexDirection: "column", backgroundColor: "#1f2937", borderBottomLeftRadius: 20, borderBottomRightRadius: 20, padding: 15 }}>
                                    <View style={{ flex: 1, flexDirection: "row", justifyContent: 'space-between', alignItems: "center" }}>
                                        <View>
                                            <Text style={{ color: "white", fontWeight: "bold", fontSize: 20 }}>{item.name}</Text>
                                        </View>
                                        <View>
                                            <Text style={{ color: "white", fontWeight: "bold", fontSize: 16 }}>{item.price} €</Text>
                                        </View>
                                    </View>
                                    <Text style={{ fontSize: 12, color: "#BFBFBF", marginTop: 5 }}>{item.description}</Text>
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
                        )}
                    />
                </View>
            )
            : 
            (
                <View style={[styles.flexContainer,styles.verticalCenter,styles.horizontalCenter]}>
                    <Text style={{ color: "white" }}>Loading...</Text>
                    <ActivityIndicator/>
                </View>
            )}
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
});
