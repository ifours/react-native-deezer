import React, {
  Component,
  View,
  Text,
  ScrollView,
  StyleSheet,
} from 'react-native';

import Item from './TracksItem';
import DeezerManager from '../services/DeezerManager';

const track = require('../mocks/track');

export default class TracksList extends Component {

  state = {
    currentTrack: { id: -1 }
  };

  componentWillMount() {
    this.playTrackWithIndex = this.playTrackWithIndex.bind(this);
  }

  playTrackWithIndex(index) {
    let track = this.props.tracks[index];
    DeezerManager.playTrack(track.id);

    this.setState({ currentTrack: track });
  }

  renderItem(track, index) {
    return <Item
      key={index}
      index={index}
      playTrackWithIndex={this.playTrackWithIndex}
      isPlaying={track.id === this.state.currentTrack.id}
      {...track} />;
  }

  render() {
    return (
      <ScrollView style={styles.container}>
        {this.props.tracks.map(this.renderItem, this)}
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
