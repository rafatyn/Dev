import { Image, Pressable, Text, TouchableOpacity, View } from 'react-native';
import { Stack } from 'expo-router';
import { createContext, useState } from 'react';

import MaterialIcons from '@expo/vector-icons/MaterialIcons';
import MaterialCommunityIcons from '@expo/vector-icons/MaterialCommunityIcons';

import '../global.css';

export const SContext = createContext({showTopMenu: false, setShowTopMenu: (value: boolean) => {} });

export default function RootLayout() {
    const [showTopMenu, setShowTopMenu] = useState(Boolean);

    return (
        <SContext.Provider value={{ showTopMenu, setShowTopMenu }}>
            <Stack screenOptions = {{
                headerStyle: { backgroundColor: "#1e2936" },
                headerTintColor: "white",
                headerTitleAlign: "left",
                headerTitle: "Ruta de la tapa",
                headerLeft: () => (
                    <View style={{ marginRight: 10 }}>
                        <MaterialCommunityIcons name="food-takeout-box" size={30} color="orange" />
                    </View>
                ),
                headerRight: () => (
                    <View>
                        <TouchableOpacity onPressIn={() => { setShowTopMenu(!showTopMenu)}} hitSlop={{ top: 30, bottom: 30, left: 30, right: 30 }}>
                            <MaterialIcons name="menu" size={24} color="white" />
                        </TouchableOpacity>
                    </View>
                )
            }}/>
        </SContext.Provider>
    );
}
