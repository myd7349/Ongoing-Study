﻿// --------------------------------------------------------------------------------------------------------------------
// <copyright file="EnumMenuItem.cs" company="PropertyTools">
//   Copyright (c) 2014 PropertyTools contributors
// </copyright>
// <summary>
//   Represents a menu item with a SelectedValue property that can bind to Enum values.
// </summary>
// --------------------------------------------------------------------------------------------------------------------

//namespace PropertyTools.Wpf
namespace Common.WPF
{
    using System;
    using System.Globalization;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Data;

    /// <summary>
    /// Represents a menu item with a SelectedValue property that can bind to Enum values.
    /// </summary>
    public class EnumMenuItem : MenuItem
    {
        /// <summary>
        /// Identifies the <see cref="SelectedValue"/> dependency property.
        /// </summary>
        public static readonly DependencyProperty SelectedValueProperty = DependencyProperty.Register(
            nameof(SelectedValue),
            typeof(object),
            typeof(EnumMenuItem),
            new FrameworkPropertyMetadata(
                null, FrameworkPropertyMetadataOptions.BindsTwoWayByDefault, SelectedValueChanged));

        /// <summary>
        /// Gets or sets the selected value.
        /// </summary>
        /// <value>The selected value.</value>
        public object SelectedValue
        {
            get
            {
                return this.GetValue(SelectedValueProperty);
            }

            set
            {
                this.SetValue(SelectedValueProperty, value);
            }
        }

        public IValueConverter ValueConverter
        {
            get => (IValueConverter)GetValue(ValueConverterProperty);
            set => SetValue(ValueConverterProperty, value);
        }

        public static readonly DependencyProperty ValueConverterProperty = DependencyProperty.Register(
            nameof(ValueConverter),
            typeof(IValueConverter),
            typeof(EnumMenuItem),
            new FrameworkPropertyMetadata(
                null,
                FrameworkPropertyMetadataOptions.BindsTwoWayByDefault,
                SelectedValueChanged));


        /// <summary>
        /// The selected value changed.
        /// </summary>
        /// <param name="d">The d.</param>
        /// <param name="e">The e.</param>
        private static void SelectedValueChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((EnumMenuItem)d).OnSelectedValueChanged();
        }

        /// <summary>
        /// Called when a menu item is clicked.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.RoutedEventArgs" /> instance containing the event data.</param>
        private void ItemClick(object sender, RoutedEventArgs e)
        {
            var newValue = ((MenuItem)sender).Tag as Enum;
            if (newValue != null && !newValue.Equals(this.SelectedValue))
            {
                this.SelectedValue = newValue;
            }
        }

        /// <summary>
        /// Called when selected value changed.
        /// </summary>
        private void OnSelectedValueChanged()
        {
            this.Items.Clear();
            if (this.SelectedValue == null)
            {
                return;
            }

            var enumType = this.SelectedValue.GetType();
            foreach (Enum value in Enum.GetValues(enumType))
            {
                object header;
                if (ValueConverter == null)
                {
                    header = value.GetDescription();
                }
                else
                {
                    header = ValueConverter.Convert(
                        value,
                        typeof(string),
                        null,
                        CultureInfo.CurrentCulture);
                }

                var mi = new MenuItem
                {
                    Header = header,
                    Tag = value
                };
                if (value.Equals(this.SelectedValue))
                {
                    mi.IsChecked = true;
                }

                mi.Click += this.ItemClick;
                this.Items.Add(mi);
            }
        }
    }
}
