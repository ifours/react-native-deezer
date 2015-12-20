/* @flow */
'use strict';

import React from 'react-native';
import Dimensions from 'Dimensions';
import Connect from './Connect';
import DeezerManager from '../services/DeezerManager';
import PlayerActions from '../actions/Player';
import ApplicationView from './ApplicationView';

const {
  Component,
  StyleSheet,
  TouchableOpacity,
  Text,
  Image,
  View,
  SliderIOS,
  ActivityIndicatorIOS,
  TouchableHighlight,
  StatusBarIOS,
  Animated,
} = React;

const SCREEN_WIDTH = Dimensions.get('window').width;

class Deezer extends Component {

  state = {
    needToConnect: false,
    isConnected: false
  };

  componentWillMount() {
    this.connectToDeezer = this.connectToDeezer.bind(this);
  }

  componentDidMount() {
    DeezerManager.checkSession(async (needToConnect) => {
      
      this.setState({ needToConnect: !needToConnect });
      needToConnect && this.getFavoritesTracks();
    });
  }

  async getFavoritesTracks() {
    let tracks = await DeezerManager.getFavoritesTracks();

    PlayerActions.setTracks(tracks.reverse());
    this.setState({ isConnected: true });
  }

  async connectToDeezer() {
    await DeezerManager.connect();
    this.getFavoritesTracks();
  }

  render() {
    let { isConnected, needToConnect } = this.state;

    return !isConnected ?
      <Image style={[styles.container, { width: SCREEN_WIDTH }]} source={require('image!dzr-launch')}>
        {needToConnect ? <Connect connect={this.connectToDeezer} /> : null}
      </Image> : <ApplicationView />;
  }
}


const styles = StyleSheet.create({
  container: {
    flex: 1,
  },

  connectContainer: {
    flex: 1,
    backgroundColor: 'transaprent',
    justifyContent: 'flex-end',
    alignItems: 'center',
  },

  buttonWrapper: {
    backgroundColor: 'rgba(0,0,0,0.7)',
    alignSelf: 'stretch',
    justifyContent: 'center',
    marginHorizontal: 40,
    marginBottom: 40,
    alignItems: 'center',
    height: 40,
  },

  button: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'center',

  },

  buttonText: {
    fontSize: 18,
    color: '#fff',
  },
});

export default Deezer;
