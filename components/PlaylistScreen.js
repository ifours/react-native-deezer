import React, {
  Component,
  View,
  Text,
  StyleSheet,
} from 'react-native';

import TracksList from './TracksList';

export default class PlaylistScreen extends Component {
  render() {
    return (
      <View style={styles.container}>
        <TracksList />
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#eee',
  },
});
