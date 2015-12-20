  /* @flow */
'use strict';

import React from 'react-native';
import FontAwesomeIcon from 'react-native-vector-icons/FontAwesome';
import IonicIcon from 'react-native-vector-icons/Ionicons';
import DeviceEventEmitter from 'RCTDeviceEventEmitter';

import Component from './Component';
import DeezerManager from '../services/DeezerManager';
import PlayerActions from '../actions/Player';

const {
  StyleSheet,
  View,
  TouchableWithoutFeedback,
} = React;

class PlayerActionsView extends Component {
  constructor(...args) {
    super(...args);

    this.onPlayPausePress = this.onPlayPausePress.bind(this);
    this.state = {
      isPaused: false
    }
  }

  componentWillMount() {
    DeviceEventEmitter.addListener(
      'player.didPause',
      this._updatePlayPauseButton.bind(this, true)
    );

    DeviceEventEmitter.addListener(
      'player.playAfterPause',
      this._updatePlayPauseButton.bind(this, false)
    );
  }

  _updatePlayPauseButton(state) {
    if (state !== this.state.isPaused) {
      PlayerActions.changePlayerStatus(!state);
      this.setState({ isPaused: state });
    }
  }

  onPlayPausePress() {
    let isPaused = this.state.isPaused;

    isPaused ? DeezerManager.play() : DeezerManager.pause();
    this._updatePlayPauseButton(!isPaused);
  }

  onBackwardPress() {
    PlayerActions.playBackward();
  }

  onForwardPress() {
    PlayerActions.playForward();
  }

  render() {
    return (
      <View style={styles.container}>
        <TouchableWithoutFeedback onPress={this.onBackwardPress} >
          <View style={styles.button} >
            <IonicIcon name="ios-skipbackward" size={28} color="rgba(255,255,255,0.7)" />
          </View>
        </TouchableWithoutFeedback>
        <TouchableWithoutFeedback onPress={this.onPlayPausePress} >
          <View style={[styles.button, { marginHorizontal: 20 }]} >
            <IonicIcon name={this.state.isPaused ? 'ios-play' : 'ios-pause'} size={28} color="rgba(255,255,255,0.7)" />
          </View>
        </TouchableWithoutFeedback>
        <TouchableWithoutFeedback onPress={this.onForwardPress} >
          <View style={styles.button} >
            <IonicIcon name="ios-skipforward" size={28} color="rgba(255,255,255,0.7)" />
          </View>
        </TouchableWithoutFeedback>
      </View>
    );
  }
};


const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    justifyContent: 'center',
    marginTop: 11,
    marginBottom: 12,
  },

  button: {
    justifyContent: 'center',
    alignItems: 'center',
    width: 40,
    height: 40,
  },
});

export default PlayerActionsView;
