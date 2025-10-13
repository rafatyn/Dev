import { Text, View, StyleSheet, FlatList, ActivityIndicator, Image, TouchableOpacity, Modal, Button } from 'react-native';
import { Link, router, Stack, useFocusEffect, useLocalSearchParams } from 'expo-router';
import * as SecureStore from 'expo-secure-store';
import { useState, useEffect, useCallback } from 'react';

import { getJsonFromUrl, getTextFromUrl } from "@/components/fetch";
import { IPath } from '@/components/types';
import Screen from '@/app/Screen';

import FontAwesome from '@expo/vector-icons/FontAwesome';
import FontAwesome6 from '@expo/vector-icons/FontAwesome6';

export default function Path() {
    const { type } = useLocalSearchParams<{ type: string }>();
    const [paths, setPaths] = useState(Array<IPath>);

    const url = 'User/' + (type == 'Liked' ? 'GetLikedItems' : 'GetBookmarkedItems') + '?Type=Path';

    useFocusEffect(
        useCallback(() => {
            var sessionId = SecureStore.getItem('sessionId');
            getJsonFromUrl(url + (sessionId != null ? "&SessionId=" + sessionId : "")).then(itemList => {
                setPaths(itemList);
            });
        }, [])
    );

    return (
        <Screen>
            <Stack.Screen
                options={{
                    headerTitle: (type == 'Liked' ? 'Liked products' : 'Saved products'),
                    headerTitleAlign: "center",
                    headerLeft: undefined
                }}
            />
            { paths != undefined && paths.length > 0 ? 
                (
                    <View style={{ flex: 1 }}>
                        <FlatList
                            data={paths.sort((a, b) => {
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
                            keyExtractor={(item) => item.link }
                            renderItem={({ item }) => (
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
                                        </View>
                                        <View style={{ flex: 1, flexDirection: "row", justifyContent: 'space-between', alignItems: "center", marginTop: 10 }}>
                                            <View style={{ display: "flex", flexDirection: "row", alignItems: "center", backgroundColor: "#374151", borderRadius: 20, padding: 5, paddingLeft: 10, paddingRight: 10 }}>
                                                <FontAwesome name="heart" size={20} color="red" />
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
