import React, {
  View,
  Text,
  Image,
  TouchableHighlight,
  StyleSheet,
} from 'react-native';

import DeezerManager from '../services/DeezerManager';
import Cover from './Cover';
import Component from './Component'
import CoverEqualizer from './CoverEqualizer';

export default class TracksItem extends Component {

  componentWillMount() {
    this.playTrack = this.playTrack.bind(this);
    this.showUnderlay = this.showUnderlay.bind(this);
    this.hideUnderlay = this.hideUnderlay.bind(this);
  }

  playTrack() {
    this.props.playTrackWithIndex(this.props.index);
  }

  showUnderlay() {
    this.view && this.view.setNativeProps({style: { backgroundColor: '#eee' }});
  }

  hideUnderlay() {
    this.view && this.view.setNativeProps({style: { backgroundColor: '#fff' }});
  }

  render() {
    let { isCurrent, title, artist: { name: artistName } , album: { cover , title: albumTitle } } = this.props;

    return (
      <TouchableHighlight
        onPress={this.playTrack}
        activeOpacity={1}
        style={styles.container}
        onShowUnderlay={this.showUnderlay}
        onHideUnderlay={this.hideUnderlay}>
        <View>
          <View ref={(view) => this.view = view} style={styles.row}>
            <Cover
              style={styles.albumCover}
              source={{uri: cover }}>
              {isCurrent && <CoverEqualizer />}
            </Cover>
            <View style={styles.info}>
              <Text style={styles.titleText} numberOfLines={1}>{title}</Text>
              <Text style={styles.artistAndAlbumText} numberOfLines={1}>
                <Text style={styles.artistNameText} >{artistName}</Text>
                <Text style={styles.albumTitleText}>{' - '}{albumTitle}</Text>
              </Text>
            </View>
          </View>
        </View>
      </TouchableHighlight>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    marginBottom: 8,
  },

  row: {
    height: 64,
    backgroundColor: '#fff',
    flexDirection: 'row',
  },

  info: {
    flex: 1,
    justifyContent: 'center',
    marginHorizontal: 16,
  },

  albumCover: {
    height: 64,
    width: 64,
  },

  titleText: {
    color: '#4e4e55',
    fontWeight: '500',
    fontSize: 15,
  },

  artistAndAlbumText: {
    fontSize: 12,
    fontWeight: '600',
    paddingTop: 3
  },

  artistNameText: {
    color: '#a0a0a7',
  },

  albumTitleText: {
    color: '#cbcbd1',
  },

});
