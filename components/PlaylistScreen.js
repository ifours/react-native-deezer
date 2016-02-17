import React, {
  Component,
  View,
  Text,
  TouchableHighlight,
  StyleSheet,
} from 'react-native';

import TracksList from './TracksList';
import DeezerManager from '../services/DeezerManager';
import IonicIcon from 'react-native-vector-icons/Ionicons';
import PlayerActions from '../actions/Player';

export default class PlaylistScreen extends Component {

  connect() {
    (async () => {
      await DeezerManager.connect();

      let tracks = await DeezerManager.getFavoritesTracks();
      PlayerActions.setTracks(tracks.reverse());
    })();
  }

  diconnect() {

  }

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.header}>
          <TouchableHighlight style={styles.buttonWrapper} onPress={this.connect.bind(this)}>
            <View style={styles.button}>
              <IonicIcon name="log-in" size={20} color="#eee" />
              <Text style={styles.buttonText}>Log In</Text>
            </View>
          </TouchableHighlight>
          <TouchableHighlight style={styles.buttonWrapper}>
            <View style={styles.button}>
              <IonicIcon name="log-out" size={20} color="#eee" />
              <Text style={styles.buttonText}>Log Out</Text>
            </View>
          </TouchableHighlight>
        </View>
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

  header: {
    height: 64,
    flexDirection: 'row',
    backgroundColor: '#fff',
  },

  buttonWrapper: {
    flex: 1,
    margin: 10,
  },

  button: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    flexDirection: 'row',
    backgroundColor: 'rgba(0,0,0,0.8)',
  },

  buttonText: {
    paddingLeft: 10,
    color: '#eee',
    fontWeight: '500',
  }
});
