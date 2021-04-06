/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React from 'react';
import type {Node} from 'react';
import ReactNative, {
  SafeAreaView,
  ScrollView,
  StatusBar,
  Text,
  useColorScheme,
  View,
  UIManager,
  Button,
  requireNativeComponent,
} from 'react-native';

import {
  Colors,
  Header,
} from 'react-native/Libraries/NewAppScreen';

const RNSimple = requireNativeComponent('RNSimple');

const App: () => Node = () => {
  const isDarkMode = useColorScheme() === 'dark';

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  let nativeCompHandle;
  let numberOfPresses = 0;

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar barStyle={isDarkMode ? 'light-content' : 'dark-content'} />
      <ScrollView
        contentInsetAdjustmentBehavior="automatic"
        style={backgroundStyle}>
        <Header />
        <View
          style={{
            backgroundColor: isDarkMode ? Colors.black : Colors.white,
            height:500,
            padding:24
          }}>
          <Text>Button to change the RNSimple contents after 1 second. Works on Debug. On Release, it waits for an UI change before sending the command.</Text>
          <Button title="ChangeText" onPress={() => {
            numberOfPresses++;
            let currentPresses = numberOfPresses;
            setTimeout( () => {
              UIManager.dispatchViewManagerCommand(
                nativeCompHandle,
                UIManager.getViewManagerConfig('RNSimple').Commands.changeText,
                [ "The button has been pressed " + currentPresses + " times." ]
              );
            }, 2000);
          }} />
          <RNSimple ref={ref => {nativeCompHandle = ReactNative.findNodeHandle(ref)}} style={{flex:1}}/>
        </View>
      </ScrollView>
    </SafeAreaView>
  );
};

export default App;
