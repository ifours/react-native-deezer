/* @flow */
'use strict';

import React from 'react-native';

import Component from './Component';
import EqualizerBar from './EqualizerBar';
import CoverEqualizer from './CoverEqualizer';
import Cover from './Cover';

const {
  StyleSheet,
  View,
  Text,
  TouchableHighlight,
} = React;

class TracksItem extends Component {

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
    return (
      <TouchableHighlight
        style={styles.container}
        activeOpacity={1}
        onPress={this.playTrack}
        onShowUnderlay={this.showUnderlay}
        onHideUnderlay={this.hideUnderlay}>
        <View>
          <View ref={(view) => this.view = view } style={styles.view}>
            <Cover width={64} height={64} source={this.props['album.cover']}>
              {this.props.isNowPlaying && <CoverEqualizer key={this.props.key} />}
            </Cover>
            <View style={styles.infoView}>
              <Text style={styles.trackTitle} numberOfLines={1}>{this.props.title}</Text>
              <Text style={styles.artistAndAlbumText} numberOfLines={1}>
                <Text style={styles.artistName}>{this.props['artist.name']}</Text>
                <Text style={styles.albumTitle}> {'-'} {this.props['album.title']}</Text>
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

  view: {
    height: 64,
    flexDirection: 'row',
    backgroundColor: '#fff',
  },

  infoView: {
    marginHorizontal: 16,
    flex: 1,
    justifyContent: 'center',
  },

  trackTitle: {
    color: '#4e4e55',
    fontWeight: '500',
    fontSize: 15,
  },

  artistAndAlbumText: {
    fontSize: 12,
    fontWeight: '600',
    paddingTop: 3
  },

  artistName: {
    color: '#a0a0a7',
  },

  albumTitle: {
    color: '#cbcbd1',
  }
});

export default TracksItem;
