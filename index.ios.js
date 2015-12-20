/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 */
'use strict';

import { AppRegistry, StatusBarIOS } from 'react-native';
import DeviceEventEmitter from 'RCTDeviceEventEmitter';
import DeezerManager from './services/DeezerManager';
import DeezerApp from './components/Deezer';
import PlayerActions from './actions/Player';


(() => {
  StatusBarIOS.setHidden(true);
  StatusBarIOS.setStyle('light-content');

  DeviceEventEmitter.addListener(
    'player.nextTrack',
    PlayerActions.playForward
  );

  DeviceEventEmitter.addListener(
    'player.previosTrack',
    PlayerActions.playBackward
  );

  AppRegistry.registerComponent('Deezer', () => DeezerApp);
})();
