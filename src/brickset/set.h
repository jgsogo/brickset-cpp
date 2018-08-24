
#pragma once

#include "include/set.h"

#include "soapBricksetAPIv2SoapProxy.h"

namespace brickset {
    namespace _detail {

        class SetReference : public Set
        {
        public:
            SetReference(ns1__sets* set);
            virtual ~SetReference();

            virtual const int& setID() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> number() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> name() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> year() const final;

        protected:
            ns1__sets * _set;
        };

        class SetDeepCopy : public Set
        {
        public:
            SetDeepCopy(ns1__sets* set, bool userHash_or_userName = false);

            virtual const int& setID() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> number() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> name() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> year() const final;

        protected:
            int _setID, _numberVariant, _ownedByTotal, _wantedByTotal,
                _reviewCount, _instructionsCount, _additionalImageCount;
            bool _image, _released;
            double _rating;
            time_t _lastUpdated;
            std::optional<bool> _owned, _wanted;
            std::optional<std::string> _number, _name, _year, _theme, _themeGroup, _subtheme,
                _imageFilename, _thumbnailURL, _largeThumbnailURL, _imageURL, _bricksetURL,
                _userNotes, _UKRetailPrice, _USRetailPrice, _CARetailPrice, _EURetailPrice,
                _USDateAddedToSAH, _USDateRemovedFromSAH, _packagingType, _availability,
                _EAN, _UPC, _description, _ageMin, _ageMax, _height, _width, _depth, _weight,
                _category, _notes, _userRating;
            std::optional<int> _pieces, _minifigs, _qtyOwned, _ACMDataCount;
            std::optional<std::vector<std::string>> _tags;
        };

} }
