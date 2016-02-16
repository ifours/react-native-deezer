/* @flow */
'use strict';
import React from 'react-native';
import EqualizerBar from './EqualizerBar';

const {
  Component,
  StyleSheet,
  View,
} = React;

class CoverEqualizer extends Component {

  render() {
    return (
      <View style={styles.container}>
        <EqualizerBar isPlaying={this.props.isPlaying} />
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
