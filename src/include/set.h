
#pragma once

#include <string>
#include <optional>

namespace brickset {

    class Set
    {
    public:
        virtual const int& setID() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> number() const = 0;
        virtual const int& numberVariant() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> name() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> year() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> theme() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> themeGroup() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> subtheme() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> pieces() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> minifigs() const = 0;
        virtual bool image() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> imageFilename() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> thumbnailURL() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> largeThumbnailURL() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> imageURL() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> bricksetURL() const = 0;
        virtual bool released() const = 0;
        virtual std::optional<std::reference_wrapper<const bool>> owned() const = 0;
        virtual std::optional<std::reference_wrapper<const bool>> wanted() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> qtyOwned() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> ACMDataCount() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> userNotes() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> ownedByTotal() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> wantedByTotal() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> UKRetailPrice() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> USRetailPrice() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> CARetailPrice() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> EURetailPrice() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> USDateAddedToSAH() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> USDateRemovedFromSAH() const = 0;
        virtual std::optional<std::reference_wrapper<const float>> rating() const = 0; //! TODO: Decimal!
        virtual std::optional<std::reference_wrapper<const int>> reviewCount() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> packagingType() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> availability() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> instructionsCount() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> additionalImageCount() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> EAN() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> UPC() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> description() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> lastUpdated() const = 0; //! TODO: This is a date!
        virtual std::optional<std::reference_wrapper<const int>> ageMin() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> ageMax() const = 0;
        virtual std::optional<std::reference_wrapper<const float>> height() const = 0; //! TODO: Decimal!
        virtual std::optional<std::reference_wrapper<const float>> width() const = 0; //! TODO: Decimal!
        virtual std::optional<std::reference_wrapper<const float>> depth() const = 0; //! TODO: Decimal!
        virtual std::optional<std::reference_wrapper<const float>> weight() const = 0; //! TODO: Decimal!
        virtual std::optional<std::reference_wrapper<const std::string>> category() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> notes() const = 0;
        virtual std::optional<std::reference_wrapper<const int>> userRating() const = 0;
        virtual std::optional<std::reference_wrapper<const std::vector<std::string>>> tags() const = 0;
    };

}
