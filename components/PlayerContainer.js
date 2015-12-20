/* @flow */
'use strict';

import React from 'react-native';
import Dimensions from 'Dimensions';
import { BlurView } from 'react-native-blur';
import PlayerInfo from './PlayerInfo';
import Component from './Component';
import AppStore from '../stores/App';
import AppActions from '../actions/App';
import PlayerStore from '../stores/Player';
import PlayerActions from '../actions/Player';

const {
  StyleSheet,
  View,
  Image,
} = React;

const SCREEN_HEIGHT = Dimensions.get('window').height;

class Player extends Component {

  constructor(...args) {
    super(...args);

    this._onChange = this._onChange.bind(this);
    this.state = {
      track: PlayerStore.getCurrentTrack()
    };
  }

  componentDidMount() {
    PlayerStore.addChangeListener(this._onChange);
  }

  componentWillUnmount() {
    PlayerStore.removeChangeListener(this._onChange);
  }

  _onChange() {
    this.setState({ track: PlayerStore.getCurrentTrack() })
  }

  render() {
    let track = this.state.track;

    return (
      <View style={styles.container}>
        <Image source={{ uri: track['album.cover'] }} style={{height: SCREEN_HEIGHT}}>
          <BlurView blurType="dark" style={{height: SCREEN_HEIGHT}}>
            <PlayerInfo
              duration={track.duration}
              cover={track['album.cover']}
              artistName={track['artist.name']}
              albumTitle={track['album.title']}
              title={track['title']} />
          </BlurView>
        </Image>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {},
});

export default Player;
