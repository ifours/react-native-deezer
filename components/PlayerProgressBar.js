/* @flow */
'use strict';

import React from 'react-native';
import Dimensions from 'Dimensions';
import DeviceEventEmitter from 'RCTDeviceEventEmitter';

import Component from './Component';
import PlayerActions from '../actions/Player';

const {
  StyleSheet,
  View,
} = React;

const SCREEN_WIDTH = Dimensions.get('window').width;

class PlayerProgressBar extends Component {

  componentWillMount() {
    DeviceEventEmitter.addListener(
      'player.didPlay',
      this._updateProgress.bind(this)
    );

    DeviceEventEmitter.addListener(
      'player.didBuffer',
      this._updateBuffer.bind(this)
    );

    this._setupValues();
    this.maxWidth = 200;
  }

  _setupValues() {
    this.didPlayedDelta = 0;
    this.didPlayed = 0;
  }

  _setupWidth(event) {
    this.maxWidth = event.nativeEvent.layout.width;
  }

  _updateProgress(value) {
    if (this.didPlayed && value > 0.9 && value + this.didPlayedDelta >= 1) {
      this._setupValues();
      return PlayerActions.playForward();
    }

    this.didPlayedDelta = value - this.didPlayed;
    this.didPlayed = value;
    this.progressBar && this.progressBar.setNativeProps({style: { width: value * this.maxWidth }});
  }

  _updateBuffer(value) {
    this.bufferBar && this.bufferBar.setNativeProps({style: { width: value * this.maxWidth }});
  }

  render() {
    return (
      <View style={styles.container} onLayout={this._setupWidth.bind(this)}>
        <View style={styles.bufferBar} ref={(bufferBar) => this.bufferBar = bufferBar } />
        <View style={styles.progressBar} ref={(progressBar) => this.progressBar = progressBar } />
      </View>
    );
  }
};


const styles = StyleSheet.create({
  container: {
    height: 2,
    backgroundColor: 'rgba(255,255,255,0.1)',
  },

  progressBar: {
    backgroundColor: '#007FE7',
    width: 0,
    height: 2,
    position: 'absolute',
    top: 0,
    left: 0,
    right: 0,
  },

  bufferBar: {
    backgroundColor: 'rgba(21,126,225, 0.3)',
    width: 0,
    height: 2, 
    position: 'absolute',
    top: 0,
    left: 0,
    right: 0,
  }
});

export default PlayerProgressBar;
