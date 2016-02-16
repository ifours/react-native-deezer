import React, {
  Component,
  View,
  Text,
  Image,
  TouchableHighlight,
  StyleSheet,
} from 'react-native';

export default class TracksItem extends Component {
  render() {
    let { title, artist: { name: artistName } , album: { cover , title: albumTitle } } = this.props;

    return (
      <TouchableHighlight
        underlayColor="#fff"
        style={styles.container} >
        <View style={styles.row}>
          <Image
            style={styles.albumCover}
            source={{uri: cover }} />
            <View style={styles.info}>
              <Text style={styles.titleText} numberOfLines={1}>{title}</Text>
              <Text style={styles.artistAndAlbumText} numberOfLines={1}>
                <Text style={styles.artistNameText} >{artistName}</Text>
                <Text style={styles.albumTitleText}>{' - '}{albumTitle}</Text>
              </Text>
            </View>
        </View>
      </TouchableHighlight>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    marginBottom: 8,
    backgroundColor: '#fff',
  },

  row: {
    height: 64,
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
