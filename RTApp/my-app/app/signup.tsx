import { Text, View, StyleSheet, Button, TextInput } from 'react-native';
import { Link, router, Stack } from 'expo-router';
import * as SecureStore from 'expo-secure-store';
import { useState } from 'react';

import Loader from "react-native-modal-loader";
import ProgressBarAnimated from 'react-native-progress-bar-animated';

import { getTextFromUrl } from "@/components/fetch";
import Screen from '@/app/Screen';

export default function Login() {
    const [userFullName, onChangeUserFullName] = useState("PruebaUser");//useState("");
    const [userName, onChangeUserName] = useState("PruebaUser");//useState("");
    const [password, onChangePassword] = useState("Prueba1234");//useState("");
    const [error, setError] = useState("");
    const [loading, setLoading] = useState(false);
    const [passwordSecurity, setPasswordSecurity] = useState(70);//useState(20);
    const [passwordSecurityColor, setPasswordSecurityColor] = useState("#FFBD31");//useState("#FF0000");

    const url = 'User/CreateUser?Name=';

    function login()
    {
        setLoading(true);
        setError("");
        getTextFromUrl(url + userFullName + "&UserName=" + userName + '&Password=' + password, 'POST').then(session => {
            if (session != undefined && session != "") {
                SecureStore.setItem('sessionId', session);
                router.dismissAll();
            } else {
                setError("Wrong fields");
            }
            setLoading(false);
        });
    }

    function calculatePasswordSecurity(password: string)
    {
        if (password.length < 8) {
            setPasswordSecurity(20);
            setPasswordSecurityColor("#FF0000");
        } else if (password.match("[0-9]") == null) {
            setPasswordSecurity(40);
            setPasswordSecurityColor("#FF0000");
        } else if (password.match("[!-\/:-@[-`{-~]") == null) {
            setPasswordSecurity(70);
            setPasswordSecurityColor("#FFBD31");
        } else {
            setPasswordSecurity(100);
            setPasswordSecurityColor("#00FF00");
        }
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
                <Text style={{ color: "white", fontSize: 24, fontWeight: "bold", textAlign: "center" }}>Create an account</Text>
                <Text style={{ color: "white", marginTop: 5 }}>Sign up to unlock more features</Text>
                {error && (
                    <View style={{ marginTop: 20, marginBottom: 20, width: '100%', height: 54, backgroundColor: '#E64949', opacity: 0.8, borderRadius: 10 }}>
                        <Text style={{ color: "white", paddingTop: 16, textAlign: "center" }}>{error}</Text>
                    </View>
                )}
                <View style={{ width: "100%", marginTop: 5 }}>
                    <Text style={{ color: "white", marginTop: 5, fontWeight: "bold" }}>Full Name</Text>
                    <TextInput
                        style={styles.textInput}
                        onChangeText={onChangeUserFullName}
                        value={userFullName}
                        placeholder="Doe John"
                        placeholderTextColor={"#AFAFAF"}
                        keyboardType="default"
                        textContentType="username"
                        autoComplete='name'
                    />
                </View>
                <View style={{ width: "100%", marginTop: 10 }}>
                    <Text style={{ color: "white", marginTop: 5, fontWeight: "bold" }}>User Name</Text>
                    <TextInput
                        style={styles.textInput}
                        onChangeText={onChangeUserName}
                        value={userName}
                        placeholder="Username"
                        placeholderTextColor={"#AFAFAF"}
                        keyboardType="default"
                        textContentType="username"
                        autoComplete='off'
                    />
                </View>
                <View style={{ width: "100%", marginTop: 10 }}>
                    <Text style={{ color: "white", marginTop: 5, fontWeight: "bold" }}>Password</Text>
                    <TextInput
                        style={[styles.textInput, { marginBottom: 10 }]}
                        onChangeText={password => { onChangePassword(password); calculatePasswordSecurity(password); }}
                        value={password}
                        placeholder="Password"
                        placeholderTextColor={"#AFAFAF"}
                        keyboardType="default"
                        textContentType="password"
                        secureTextEntry={true}
                    />
                    {password && (
                        <View style={{ width: "100%", alignItems: "center" }}>
                            <ProgressBarAnimated
                                width={300}
                                value={passwordSecurity}
                                backgroundColor={passwordSecurityColor}
                            />
                        </View>
                    )}
                </View>
                <View style={{ width: "100%", marginTop: 20 }}>
                    <Button title='Sign Up' onPress={login} disabled={userFullName.length == 0 || userName.length == 0 || password.length == 0 || passwordSecurity < 70}/>
                </View>
                <View style={{ flex: 1, flexDirection: "row", maxHeight: 30, marginTop: 20, alignItems: "center", justifyContent: "center" }}>
                    <Text style={{ color: "white", marginTop: 5 }}>Already have an account? </Text>
                    <Link href="/login" asChild>
                        <Text style={{ color: "white", textDecorationLine: "underline", marginTop: 5 }}>Sign In</Text>
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
