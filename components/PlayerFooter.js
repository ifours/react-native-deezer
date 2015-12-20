/* @flow */
'use strict';

import React from 'react-native';
import FontAwesomeIcon from 'react-native-vector-icons/FontAwesome';
import IonicIcon from 'react-native-vector-icons/Ionicons';

import Component from './Component';
import PlayerControls from './PlayerControls';
import PlayerProgressBar from './PlayerProgressBar';
import PlayerVolume from './PlayerVolume';

const {
  StyleSheet,
  View,
  Text,
} = React;

class PlayerControlls extends Component {
  render() {
    return (
      <View style={styles.container}>
        <PlayerProgressBar />
        <PlayerControls />
        <PlayerVolume />
        <View style={{ height: 2, backgroundColor: 'rgba(255,255,255,0.1)' }}/>
        <View style={{ alignItems: 'center', justifyContent: 'center', height: 47}}>
          <Text style={{color: 'rgba(255,255,255,0.6)' }}>Deezer App by Ilja Satchok</Text>
        </View>
      </View>
    );
  }
};

const styles = StyleSheet.create({
  container: {
    position: 'absolute',

    bottom: 0,
    left: 0,
    right: 0,
    backgroundColor: 'rgba(25,25,33, 0.3)',
  }
});

export default PlayerControlls;
