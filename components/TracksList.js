import React, {
  Component,
  View,
  Text,
  ScrollView,
  StyleSheet,
} from 'react-native';

import Item from './TracksItem';

const track = require('../mocks/track');

export default class TracksList extends Component {
  state = {
    tracks: [track, track, track,track, track, track,track, track, track,track, track, track]
  };

  renderItem(track, index) {
    return <Item key={index} {...track} />;
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
