import React, {
  Component,
  View,
  Text,
  ScrollView,
  StyleSheet,
} from 'react-native';

import Item from './TracksItem';
import DeezerManager from '../services/DeezerManager';
import PlayerStore from '../stores/Player';
import PlayerActions from '../actions/Player';

const track = require('../mocks/track');

export default class TracksList extends Component {

  state = {
    currentTrack: PlayerStore.getCurrentTrack(),
    isPlaying: PlayerStore.isPlaying(),
    tracks: PlayerStore.getTracks()
  };

  componentWillMount() {
    this.playTrackWithIndex = this.playTrackWithIndex.bind(this);

    PlayerStore.addChangeListener(this._onChange.bind(this));
  }

  _onChange() {
    this.setState({
      currentTrack: PlayerStore.getCurrentTrack(),
      tracks: PlayerStore.getTracks(),
      isPlaying: PlayerStore.isPlaying(),
    });
  }

  playTrackWithIndex(index) {
    let track = this.state.tracks[index];

    if (track === this.state.currentTrack) {
      this.state.isPlaying ? PlayerActions.pause() : PlayerActions.play();
    } else {
      PlayerActions.setCurrentTrackWithIndex(track, index);
    }

  }

  renderItem(track, index) {
    return <Item
      key={index}
      index={index}
      playTrackWithIndex={this.playTrackWithIndex}
      isCurrent={track.id === this.state.currentTrack.id}
      {...track} />;
  }

  render() {
    return (
      <ScrollView style={styles.container}>
        {this.state.tracks.map(this.renderItem, this)}
      </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    padding: 8,
    paddingTop: 4,
  },
});
