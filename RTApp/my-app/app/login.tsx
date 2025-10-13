import { Text, View, StyleSheet, Button, TextInput, TouchableOpacity } from 'react-native';
import { Link, router, Stack } from 'expo-router';
import * as SecureStore from 'expo-secure-store';
import { useState } from 'react';
import Loader from "react-native-modal-loader";

import { getTextFromUrl } from "@/components/fetch";
import Screen from '@/app/Screen';

export default function Login() {
    const [userName, onChangeUserName] = useState("PruebaUser");
    const [password, onChangePassword] = useState("Prueba1234");
    const [error, setError] = useState<String>();
    const [loading, setLoading] = useState<boolean>(false);

    const url = 'User/Login?UserName=';

    function login()
    {
        setLoading(true);
        setError("");
        getTextFromUrl(url + userName + '&Password=' + password, 'POST').then(session => {
            if (session != undefined && session != "") {
                SecureStore.setItem('sessionId', session);
                router.back();
            } else {
                setError("Wrong credentials");
            }
            setLoading(false);
        });
    }

    return (
        <Screen>
            <Stack.Screen
                options={{
                    headerTitle: "Log In",
                    headerTitleAlign: "center",
                    headerRight: undefined
                }}
            />
            <View style={[styles.container, styles.verticalCenter, styles.horizontalCenter]}>
                <Loader loading={loading} color="#ff66be" />
                <Text style={{ color: "white", fontSize: 24, fontWeight: "bold", textAlign: "center" }}>Welcome back</Text>
                <Text style={{ color: "white", marginTop: 5 }}>Sign in to your account</Text>
                {error && (
                    <View style={{ marginTop: 20, marginBottom: 20, width: '100%', height: 54, backgroundColor: '#E64949', opacity: 0.8, borderRadius: 10 }}>
                        <Text style={{ color: "white", paddingTop: 16, textAlign: "center" }}>{error}</Text>
                    </View>
                )}
                <View style={{ width: "100%", marginTop: 5 }}>
                    <Text style={{ color: "white", marginTop: 5, fontWeight: "bold" }}>User Name</Text>
                    <TextInput
                        style={styles.textInput}
                        onChangeText={onChangeUserName}
                        value={userName}
                        placeholder="Username"
                        placeholderTextColor={"#AFAFAF"}
                        keyboardType="default"
                        textContentType="username"
                        autoComplete='username'
                    />
                </View>
                <View style={{ width: "100%", marginTop: 10 }}>
                    <Text style={{ color: "white", marginTop: 5, fontWeight: "bold" }}>Password</Text>
                    <TextInput
                        style={styles.textInput}
                        onChangeText={onChangePassword}
                        value={password}
                        placeholder="Password"
                        placeholderTextColor={"#AFAFAF"}
                        keyboardType="default"
                        textContentType="password"
                        secureTextEntry={true}
                    />
                </View>
                <View style={{ width: "100%", marginTop: 20 }}>
                    <Button title='Sign In' onPress={login} disabled={userName.length == 0 || password.length == 0}/>
                </View>
                <View style={{ flex: 1, flexDirection: "row", maxHeight: 30, marginTop: 20, alignItems: "center", justifyContent: "center" }}>
                    <Text style={{ color: "white", marginTop: 5 }}>Don't have an account? </Text>
                    <Link href="/signup" asChild>
                        <Text style={{ color: "white", textDecorationLine: "underline", marginTop: 5 }}>Sign Up</Text>
                    </Link>
                </View>
            </View>
        </Screen>
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        padding: 20
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
    textInput: {
        color: "white", 
        borderColor: "#CFCFCF", 
        borderStyle: "solid", 
        borderRadius: 5, 
        borderWidth: 0.5, 
        marginTop: 5,
        padding: 15
    }
});
