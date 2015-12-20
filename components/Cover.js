/* @flow */
'use strict';
import React from 'react-native';

import Component from './Component';

const {
  StyleSheet,
  View,
  Image,
  Animated,
} = React;

class Cover extends Component {

  componentWillMount() {
    this.opacity = new Animated.Value(0);
  }

  omImageLoad() {
    Animated.timing(this.opacity, {
      toValue: 1,
      duration: 200,
    }).start();
  }

  render() {
    let coverImageStyles = {
      width: this.props.width,
      height: this.props.height
    };

    let defaultCover = this.props.size === 'large' ?
      require('image!cover-182x182') :
      require('image!cover');

    return (
      <View style={styles.conteiner}>
        <Image
          style={[coverImageStyles]}
          source={defaultCover}
          resizeMode="contain">
          <Animated.Image
            style={[styles.coverImage, coverImageStyles, { opacity: this.opacity }]}
            source={{ uri: this.props.source }} 
            onLoad={this.omImageLoad.bind(this)} >
            <View style={[styles.coverImage, styles.equalizer]} >
              {this.props.children}
            </View>
          </Animated.Image>
        </Image>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  conteiner: {},

  coverImage: {
    position: 'absolute',

    top: 0,
    left: 0,
    right: 0,
    bottom: 0,
  },

  equalizer:{
    justifyContent: 'center',
    alignItems: 'center',
    flex: 1,
    backgroundColor: 'rgba(0,0,0,0)'
  }
});

export default Cover;
