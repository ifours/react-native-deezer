/* @flow */
'use strict';

import React from 'react-native';
import Component from './Component';

const {
  StyleSheet,
  View,
  Animated,
} = React;

const MAX_HEIGHT = 20;
const MIN_HEIGHT = 1;

class EqualizerBar extends Component {

  componentWillMount() {
    this.value = Math.max(this.props.value * MAX_HEIGHT, MIN_HEIGHT);
    this.anim = new Animated.Value(this.value);
    this.interpolation = this.anim.interpolate({
      inputRange: this._getInputRange(),
      outputRange: this._getOutputRange()
    });
  }

  componentDidMount() {
    this.props.registerAnimation(this.anim);
  }

  _getInputRange() {
    return [
      -1,
      this.props.value - 1,
      0,
      this.props.value,
      1
    ];
  }

  _getOutputRange() {
    return [
      this.value,
      MIN_HEIGHT,
      Math.max(MAX_HEIGHT - this.value, MIN_HEIGHT),
      MAX_HEIGHT,
      this.value
    ];
  }

  render() {
    return (
      <Animated.View
        style={[styles.bar, {
          height: this.interpolation,
          marginHorizontal: this.props.middle ? 1 : 0
        }]} />
    );
  }
}

const styles = StyleSheet.create({
  bar: {
    width: 4,
    backgroundColor: '#fff',
  },
});

export default EqualizerBar;
