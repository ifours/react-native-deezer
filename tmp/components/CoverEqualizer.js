/* @flow */
'use strict';
import React from 'react-native';
import EqualizerBar from './EqualizerBar';
import Component from './Component'
import PlayerStore from '../stores/Player';

const {
  StyleSheet,
  View,
} = React;

class CoverEqualizer extends Component {
  constructor(...args) {
    super(...args);

    this._onChange = this._onChange.bind(this);

    this.state = {
      isPlaying: PlayerStore.isPlaying()
    }
  }

  componentDidMount() {
    PlayerStore.addChangeListener(this._onChange);
  }

  componentWillUnmount() {
    this.isUnmounted = true;
    PlayerStore.removeChangeListener(this._onChange);
  }

  _onChange() {
    if (!this.isUnmounted) {
      this.setState({ isPlaying: PlayerStore.isPlaying() });
    }
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
