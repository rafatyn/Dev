import { Text, View, StyleSheet, FlatList, ActivityIndicator, Pressable, Button, TouchableOpacity, Image, Modal, ScrollView } from 'react-native';
import { Link, Stack } from 'expo-router';

import Screen from '@/app/Screen';
import FontAwesome from '@expo/vector-icons/FontAwesome';
import MaterialIcons from '@expo/vector-icons/MaterialIcons';


export default function Index() {

    return (
        <Screen>
            <Stack.Screen
                options={{
                    headerTitle: "Profile",
                    headerTitleAlign: "center",
                    headerLeft: undefined
                }}
            />
            <View>
                <View style={{ display: 'flex', alignItems: 'center', marginTop: 50 }}>
                    <FontAwesome name="user-circle" size={80} color="white" />
                </View>
                <ScrollView contentContainerStyle={{ marginTop: 50 }}>
                    <View style={{ padding: 25, paddingRight: 15, borderColor: 'white', borderTopWidth: .5 }}>
                        <Link href={{ pathname: '/userPaths', params: { type: 'Liked' } }} asChild>
                            <TouchableOpacity>
                                <View style={{ display: 'flex', flexDirection: 'row', justifyContent: 'space-between' }}>
                                    <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>View liked paths</Text>
                                    <MaterialIcons name="keyboard-arrow-right" size={24} color="#3b82f6" />
                                </View>
                            </TouchableOpacity>
                        </Link>
                    </View>
                    <View style={{ padding: 25, paddingRight: 15, borderColor: 'white', borderTopWidth: .5 }}>
                        <Link href={{ pathname: '/userProducts', params: { type: 'Liked' } }} asChild>
                            <TouchableOpacity>
                                <View style={{ display: 'flex', flexDirection: 'row', justifyContent: 'space-between' }}>
                                    <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>View liked products</Text>
                                    <MaterialIcons name="keyboard-arrow-right" size={24} color="#3b82f6" />
                                </View>
                            </TouchableOpacity>
                        </Link>
                    </View>
                    <View style={{ padding: 25, paddingRight: 15, borderColor: 'white', borderTopWidth: .5, borderBottomWidth: .5 }}>
                        <Link href={{ pathname: '/userProducts', params: { type: 'Bookmark' } }} asChild>
                            <TouchableOpacity>
                                <View style={{ display: 'flex', flexDirection: 'row', justifyContent: 'space-between' }}>
                                    <Text style={{ color: "white", fontSize: 16, fontWeight: "500" }}>View saved products</Text>
                                    <MaterialIcons name="keyboard-arrow-right" size={24} color="#3b82f6" />
                                </View>
                            </TouchableOpacity>
                        </Link>
                    </View>
                </ScrollView>
            </View>
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
