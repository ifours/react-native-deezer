/* @flow */
'use strict';
import React from 'react-native';
import EqualizerBarItem from './EqualizerBarItem';
import Component from './Component';

const {
  StyleSheet,
  View,
  Easing,
  Animated,
} = React;

class EqualizerBar extends Component {
  componentWillMount() {
    this._coreAnimation = [];
    this.registerAnimation = this.registerAnimation.bind(this);
  }

  componentDidMount() {
    requestAnimationFrame(() => {
      this.animate(false);
    }); 
  }

  componentWillReceiveProps(nextProps) {
    if (nextProps.isPlaying !== this.props.isPlaying) {
      if (!nextProps.isPlaying) {
        this.equalizerAnimation.stop();
      } else {
        this.equalizerAnimation.start(endState => {
          endState.finished && requestAnimationFrame(() => {
            this.animate(false);
          });
        });
      }
    }
  }

  animate(up) {
    this.equalizerAnimation = Animated.parallel(this._coreAnimation.map((anim) => {
      anim.setValue(up ? 0 : -1);

      return Animated.timing(anim, {
        toValue: up ? 1 : 0,
        easing: Easing.linear,
        duration: 190 * 1.8
      });
    }));

    this.equalizerAnimation.start(endState => {
      endState.finished && requestAnimationFrame(() => {
        this.animate(!up);
      });
    });
  }

  registerAnimation(animation) {
    this._coreAnimation.push(animation);
  }

  render() {
    return (
      <View style={styles.container}>
        <EqualizerBarItem value={0.5} registerAnimation={this.registerAnimation} />
        <EqualizerBarItem value={0} middle registerAnimation={this.registerAnimation} />
        <EqualizerBarItem value={1} registerAnimation={this.registerAnimation} />
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    height: 30,
    flexDirection: 'row',
    alignItems: 'flex-end',
  }
});

export default EqualizerBar;
