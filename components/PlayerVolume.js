/* @flow */
'use strict';

import React from 'react-native';
import IonicIcon from 'react-native-vector-icons/Ionicons';
import FontAwesomeIcon from 'react-native-vector-icons/FontAwesome';
import Component from './Component';
import VolumeSlider from 'react-native-volume-slider';

const {
  StyleSheet,
  View,
} = React;

class PlayerVolume extends Component {

  constructor() {
    super();

    this.volumeChange = this.volumeChange.bind(this);
    this.state = {
      volumeIcon: 'volume-down'
    };
  }

  volumeChange(value) {
    if (value < 0.2) {
      return this.setState({ volumeIcon: 'volume-off' });
    } else if (value < 0.6) {
      return this.setState({ volumeIcon: 'volume-down' });
    } else {
      return this.setState({ volumeIcon: 'volume-up' });
    }
  }

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.sliderView}>
          <FontAwesomeIcon name={this.state.volumeIcon} style={{ width: 20 }} size={18} color="rgba(255,255,255,0.6)" />
          <VolumeSlider
            style={styles.slider}
            thumbSize={{
              width: 8,
              height: 8
            }}
            thumbTintColor="rgb(146,146,157)"
            minimumTrackTintColor="rgb(146,146,157)"
            maximumTrackTintColor="rgba(255,255,255, 0.1)"
            onValueChange={this.volumeChange} />
        </View>
      </View>
    );
  }
};

const styles = StyleSheet.create({
  container: {
    marginBottom: 3
  },

  sliderView: {
    paddingHorizontal: 20,
    height: 30,
    flexDirection: 'row',
    flex: 1,
  },

  slider: {
    height: 30,
    marginLeft: 7,
  }
});

export default PlayerVolume;
