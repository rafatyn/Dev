import { Text, TouchableOpacity, Pressable, View } from "react-native";

import { SContext } from "@/app/_layout";
import { useCallback, useContext, useState } from "react";
import { Link, router, useFocusEffect } from "expo-router";
import * as SecureStore from 'expo-secure-store';
import Loader from "react-native-modal-loader";

import { getTextFromUrl } from "@/components/fetch";

export default function Screen({ children }: any) {
    const [sessionId, setSessionId] = useState<string | null>(null);
    const { showTopMenu, setShowTopMenu } = useContext(SContext);
    const [loading, setLoading] = useState<boolean>(false);

    const url = 'User/Logoff?SessionId=';

    useFocusEffect(
        useCallback(() => {
            setSessionId(SecureStore.getItem('sessionId'));
        }, [])
    );

    function logoff()
    {
        setLoading(true);
        getTextFromUrl(url + sessionId, 'POST').then(session => {
            SecureStore.deleteItemAsync('sessionId');
            setLoading(false);
            setShowTopMenu(false);
            if (router.canDismiss()) {
                router.dismissAll();
            } else {
                router.replace('/');
            }
        });
    }

    return (
        <View style={{ flex: 1 }}>
            <Loader loading={loading} color="#101927" />
            <Pressable onPress={() => { setShowTopMenu(false) }} style={{ flexGrow: 1 }}>
                <View style={{ backgroundColor: '#111827', padding: 20 }} className="flex flex-grow pt-2">{children}</View>
            </Pressable>
            {showTopMenu && (
                <View style={{ position: "absolute", right: 0, width: 80, backgroundColor: "#1f2937" }}>
                    {sessionId == null ? 
                    (
                        <Link href="/login" asChild>
                            <TouchableOpacity onPress={() => { setShowTopMenu(false) }}>
                                <Text style={{ color: "white", padding: 10 }}>Sign In</Text>
                            </TouchableOpacity>
                        </Link>
                    )
                    :
                    (
                        <View>
                            <Link href="/profile" asChild>
                                <TouchableOpacity onPress={() => { setShowTopMenu(false) }}>
                                    <Text style={{ color: "white", padding: 10 }}>Profile</Text>
                                </TouchableOpacity>
                            </Link>
                            <TouchableOpacity onPress={() => { logoff() }}>
                                <Text style={{ color: "white", padding: 10 }}>Log Off</Text>
                            </TouchableOpacity>
                        </View>
                    )}
                </View>
            )}
        </View>
    );
}