/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 */
'use strict';
import { AppRegistry, StatusBarIOS } from 'react-native';
import DeviceEventEmitter from 'RCTDeviceEventEmitter';
import PlayerActions from './actions/Player';
import App from './components/App';

(() => {

  DeviceEventEmitter.addListener(
    'player.nextTrack',
    PlayerActions.playForward
  );

  DeviceEventEmitter.addListener(
    'player.previosTrack',
    PlayerActions.playBackward
  );

  AppRegistry.registerComponent('Deezer', () => App);
})();
