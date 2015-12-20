/* @flow */
'use strict';

import React from 'react-native';
import DeviceEventEmitter from 'RCTDeviceEventEmitter';

import Component from './Component';

const {
  StyleSheet,
  View,
  Text,
  Image,
  TouchableHighlight,
} = React;

class PlayerProgressTime extends Component {
  state = {
    playProgress: 0
  };

  componentWillMount() {
    DeviceEventEmitter.addListener(
      'player.didPlay',
      (playProgress) => this.setState({ playProgress })
    );
  }

  _getPlayProgress() {
    let time = Math.floor(this.state.playProgress * this.props.duration) || 0;
     
    let minutes = Math.floor(time / 60);
    let seconds = time - minutes * 60;

    return `${minutes > 9 ? minutes : '0' + minutes}:${seconds > 9 ? seconds : '0' + seconds}`;
  }

  _getTime() {
    let time = this.props.duration || 0;

    let minutes = Math.floor(time / 60);
    let seconds = time - minutes * 60;

    return `${minutes > 9 ? minutes : '0' + minutes}:${seconds > 9 ? seconds : '0' + seconds}`;
  }

  render() {
    return (
      <View style={styles.container}>
        <View style={{flex: 1}}>
          <Text style={[styles.timeLabel, { textAlign: 'left' }]} >{this._getPlayProgress()}</Text>
        </View>
        <View style={{flex: 1, alignItems: 'flex-end'}}>
          <Text style={[styles.timeLabel, { textAlign: 'right' }]} >{this._getTime()}</Text>
        </View>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    marginTop: 5,
    alignItems: 'center',
    flexDirection: 'row',
  },

  timeLabel: {
    color: 'rgba(255,255,255,0.5)',
    fontSize: 11,
    fontWeight: '500',
    width: 40,
  }
});

export default PlayerProgressTime;
