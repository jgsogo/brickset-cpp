
#include "set.h"

#include <assert.h>
#include <sstream>

namespace brickset {
    namespace _detail {

        SetReference::SetReference(ns1__sets* set) : _set(set) {}
        SetReference::~SetReference() {}

        const int& SetReference::setID() const { return _set->setID; }

        std::optional<std::reference_wrapper<const std::string>> SetReference::number() const
        {
            return _set->number ? std::optional<std::reference_wrapper<const std::string>>{*_set->number} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetReference::name() const
        {
            return _set->name ? std::optional<std::reference_wrapper<const std::string>>{*_set->name} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetReference::year() const
        {
            return _set->year ? std::optional<std::reference_wrapper<const std::string>>{*_set->year} : std::nullopt;
        }

        SetDeepCopy::SetDeepCopy(ns1__sets* set, bool userHash_or_userName = false)
        {
            _setID = set->setID;
            if (set->number) _number = *set->number;
            _numberVariant = set->numberVariant;
            if (set->name) _name = *set->name;
            if (set->year) _year = *set->year;
            if (set->theme) _theme = *set->theme;
            if (set->themeGroup) _themeGroup = *set->themeGroup;
            if (set->subtheme) _subtheme = *set->subtheme;
            if (set->pieces) _pieces = atoi(set->pieces->c_str());
            if (set->minifigs) _minifigs = atoi(set->minifigs->c_str());
            _image = set->image;
            if (set->imageFilename) _imageFilename = *set->imageFilename;
            if (set->thumbnailURL) _thumbnailURL = *set->thumbnailURL;
            if (set->largeThumbnailURL) _largeThumbnailURL = *set->largeThumbnailURL;
            if (set->imageURL) _imageURL = *set->imageURL;
            if (set->bricksetURL) _bricksetURL = *set->bricksetURL;
            _released = set->released;
            if (userHash_or_userName) // Fields only retrieved if userHash or userName is passed to method.
            {
                _owned = set->owned;
                _wanted = set->wanted;
                _qtyOwned = set->qtyOwned;
                _ACMDataCount = set->ACMDataCount;
                if (set->userNotes) _userNotes = *set->userNotes;
            }
            else
            {
                assert(!set->owned);
                assert(!set->wanted);
                assert(set->qtyOwned == 0);
                assert(set->ACMDataCount == 0);
                assert(set->userNotes == nullptr);
            }
            _ownedByTotal = set->ownedByTotal;
            _wantedByTotal = set->wantedByTotal;
            if (set->UKRetailPrice) _UKRetailPrice = *set->UKRetailPrice;
            if (set->USRetailPrice) _USRetailPrice = *set->USRetailPrice;
            if (set->CARetailPrice) _CARetailPrice = *set->CARetailPrice;
            if (set->EURetailPrice) _EURetailPrice = *set->EURetailPrice;
            if (set->USDateAddedToSAH) _USDateAddedToSAH = *set->USDateAddedToSAH;
            if (set->USDateRemovedFromSAH) _USDateRemovedFromSAH = *set->USDateRemovedFromSAH;
            _rating = std::atof(set->rating.c_str());
            _reviewCount = set->reviewCount;
            if (set->packagingType) _packagingType = *set->packagingType;
            if (set->availability) _availability = *set->availability;
            _instructionsCount = set->instructionsCount;
            _additionalImageCount = set->additionalImageCount;
            if (set->EAN) _EAN = *set->EAN;
            if (set->UPC) _UPC = *set->UPC;
            if (set->description) _description = *set->description; // Returned only with call to getSet
            _lastUpdated = set->lastUpdated;
            if (set->ageMin) _ageMin = *set->ageMin;
            if (set->ageMax) _ageMax = *set->ageMax;
            if (set->height) _height = *set->height;
            if (set->width) _width = *set->width;
            if (set->depth) _depth = *set->depth;
            if (set->weight) _weight = *set->weight;
            if (set->category) _category = *set->category;
            if (set->notes) _notes = *set->notes; //! Returned only with call to getSet
            if (set->userRating) _userRating = *set->userRating;
            if (set->tags) //!  Returned only with call to getSet
            {
                std::vector<std::string> v;
                std::stringstream ss(*set->tags);
                while (ss.good())
                {
                    std::string substr;
                    std::getline(ss, substr, ',');
                    v.push_back(substr);
                }
                _tags = v;
            }
        }

        const int& SetDeepCopy::setID() const { return _setID; }

        std::optional<std::reference_wrapper<const std::string>> SetDeepCopy::number() const
        {
            return _number.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_number.value()} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetDeepCopy::name() const
        {
            return _name.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_name.value()} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetDeepCopy::year() const
        {
            return _year.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_year.value()} : std::nullopt;
        }

    }
}


