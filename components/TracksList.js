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

  renderItem(track, index) {
    return <Item key={index} {...track} />;
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
