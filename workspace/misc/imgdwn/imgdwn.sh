#!/bin/bash
################################################
# Image Downloader Script
# 
# Downloads all files with indexed names
#
# This will download all files from 
# http://szcdn1.raagalahari.com/mar2012/starzone/tamanna_green_transparent_saree/tamanna_green_transparent_saree1.jpg to
# http://szcdn1.raagalahari.com/mar2012/starzone/tamanna_green_transparent_saree/tamanna_green_transparent_saree93.jpg
# 
# FOLDER_NAME="Tamanna1"
# BASE_URL="http://szcdn1.raagalahari.com/mar2012/starzone/tamanna_green_transparent_saree/"
# FILE_NAME="tamanna_green_transparent_saree"
# EXTN=".jpg"
# FIRST_FILE=1
# LAST_FILE=93
#
# TODO: ADD Command Line Args
################################################

FOLDER_NAME="Tamanna7"
BASE_URL="http://www.idlebrain.com/movie/photogallery/tamanna71/images/"
FILE_NAME="tamanna"
EXTN=".jpg"
FIRST_FILE=4
LAST_FILE=10

if [ ! -d "$FOLDER_NAME" ]; then
  echo "Creating Folder $FOLDER_NAME ..."
  mkdir "$FOLDER_NAME"
else
  echo "$FOLDER_NAME already exists..."
fi

for ((i=$FIRST_FILE; i <= $LAST_FILE; i++)) 
do
  if wget -q -O "./$FOLDER_NAME/$FILE_NAME$i$EXTN" "$BASE_URL$FILE_NAME$i$EXTN" ; then
    echo "$FILE_NAME$i$EXTN downloaded..."
  else
    echo "Error downloading file $FILE_NAME$i$EXTN..."
  fi
done

echo "Finished!" 

