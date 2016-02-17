/* @flow */
'use strict';
import React from 'react-native';
import EqualizerBar from './EqualizerBar';
import PlayerStore from '../stores/Player';

const {
  Component,
  StyleSheet,
  View,
} = React;

class CoverEqualizer extends Component {

  state = {
    isPlaying: PlayerStore.isPlaying()
  };

  componentWillMount() {
    PlayerStore.addChangeListener(() => {
      !this.isUnmount && this.setState({
        isPlaying: PlayerStore.isPlaying()
      });
    });
  }

  componentWillUnmount() {
    this.isUnmount = true;
  }

  render() {
    return (
      <View style={styles.container}>
        <EqualizerBar isPlaying={this.state.isPlaying} />
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    alignItems: 'center',
    width: 44,
    height: 44,
    borderWidth: 2,
    borderRadius: 22,
    borderColor: 'rgba(255,255,255,0.6)',
    backgroundColor: 'rgba(0,0,0,0.7)',
  }
});

export default CoverEqualizer;
